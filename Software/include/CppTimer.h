#ifndef __CPP_TIMER_H_
#define __CPP_TIMER_H_

/**
 * GNU GENERAL PUBLIC LICENSE
 * Version 3, 29 June 2007
 *
 * (C) 2018, Bernd Porr <mail@bernporr.me.uk>
 *
 * This is inspired by the timer_create man page.
 **/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

#define CLOCKID CLOCK_MONOTONIC
#define SIG SIGRTMIN

class CppTimer {

private:

	timer_t timerid;
	struct sigevent sev;
	struct sigaction sa;
	struct itimerspec its;

	static void handler(int sig, siginfo_t *si, void *uc ) {
		(reinterpret_cast<CppTimer *> (si->si_value.sival_ptr))->timerEvent();
	}

public:
	CppTimer() {
		// We create a static handler catches the signal SIG
		sa.sa_flags = SA_SIGINFO;
		sa.sa_sigaction = handler;
		sigemptyset(&sa.sa_mask);
		if (sigaction(SIG, &sa, NULL) == -1)
			throw("Could not create signal handler");

		// Create the timer
		sev.sigev_notify = SIGEV_SIGNAL;
		sev.sigev_signo = SIG;
		// Cruical is that the signal carries the pointer to this class instance here
		// because the handler just handles anything that comes in!
		sev.sigev_value.sival_ptr = this;
		// create the timer
		if (timer_create(CLOCKID, &sev, &timerid) == -1)
			throw("Could not create timer");
	};

	virtual ~CppTimer() {
		// delete the timer
		timer_delete(timerid);
		// default action for signal handling
		signal(SIG, SIG_IGN);
	}

	// start the timer
	void start(long millisecs) {
		// starts instantly
		its.it_value.tv_sec = 0;
		its.it_value.tv_nsec = 1;
		its.it_interval.tv_sec = millisecs / 100;
		its.it_interval.tv_nsec = millisecs % 100;
		if (timer_settime(timerid, 0, &its, NULL) == -1)
			throw("Could not start timer");
	}

	// is implemented by its children
	// this is exectuted once "start" has been called
	virtual void timerEvent() = 0;

};


#endif
