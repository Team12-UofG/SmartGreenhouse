# Installation #

This installation guide assumes the use of the [BASH](https://en.wikipedia.org/wiki/Bash_(Unix_shell)) Unix shell and a 64-bit Linux system. Neptune may either be installed directly or as a [Bioconda](https://bioconda.github.io/) package. Neptune may either be run on a single machine or a computing cluster. Neptune achieves maximum parallelization when submitting jobs through a DRMAA-compliant cluster computing scheduler. The installation and configuration of a DRMAA-compliant scheduler will require a significant understanding of Unix. However, it is possible to run Neptune in parallel on a single machine without DRMAA. Neptune is known to be compatible with the [SGE](http://gridscheduler.sourceforge.net/) and [Slurm](http://slurm.schedmd.com/) schedulers.

## Bioconda ##

The simpliest way to install Neptune is using the [Bioconda](https://bioconda.github.io/) channel for the [conda](https://conda.io/docs/intro.html) package management system. We recommend installing conda with the [Miniconda](https://conda.io/miniconda.html) package. There are two variants of the Miniconda installer: Python 2.7 and Python 3.6. However, the choice of Miniconda only affects the Python version in root environment. We recommend installing Miniconda using Python 2.7 64-bit Linux [installer](https://repo.continuum.io/miniconda/Miniconda2-latest-Linux-x86_64.sh). Otherwise, you will need to explicitly use Neptune within a [conda environment](https://conda.io/docs/using/envs.html).

### Overview ###

The Bioconda-based Neptune installation involves the following:

 1. Installing [Bioconda](https://bioconda.github.io/)
 2. Installing the "neptune" Bioconda package (`conda install neptune`).

We provide detailed instructions below.

### Miniconda (Python 2.7) ###

[Bioconda](https://bioconda.github.io/) requires conda to be installed and we recommend using the [Miniconda](https://conda.io/miniconda.html) package. Miniconda may be installed with the follow instructions:

```bash
wget https://repo.continuum.io/miniconda/Miniconda2-latest-Linux-x86_64.sh
chmod 755 Miniconda2-latest-Linux-x86_64.sh
./Miniconda2-latest-Linux-x86_64.sh
```

You will likely want Miniconda to append the install location to your PATH and will need to select this option during the installation process. After installation, you will then need to either open a new terminal or source your bashrc file in the current terminal for Miniconda to become available on the PATH:

```bash
source ~/.bashrc
```

You can check if your Miniconda installation was successful with the following:

```bash
conda --version
```

### Bioconda ###

You will need to add the following channels to conda. They must be added in this order so that priority is set correctly.

```bash
conda config --add channels conda-forge
conda config --add channels defaults
conda config --add channels r
conda config --add channels bioconda
```

### Neptune (Miniconda 2.7) ###

The following instructions assume you are using Miniconda with Python 2.7, as described above. After enabling Bioconda, Neptune may be installed as a Bioconda package with the following:

```bash
conda install neptune
```

You can check if Neptune was installed correctly with the following:

```bash
neptune --version
```

### Neptune (Miniconda 3.6) ###

The follwing instructions assume you are using the Python 3.6 version of Miniconda. In this circumstance, we need to install Neptune within a Python 2.7 environment:

```bash
conda create --name neptune python=2.7 neptune
```

This Neptune environment can be activated with the following:

```bash
source activate neptune
```

You can check if Neptune was installed correctly with the following:

```bash
neptune --version
```

The current environment may be deactivated with the following:

```bash
source deactivate
```

It is important to note that this Neptune Bioconda environment will need to be activated in order to run the Neptune application. However, the benefit is that your system will be shielded from the Python 2.7 installation required by Neptune.

## Direct ##

The following instructions describe how to install Neptune directly. These instructions will likely require administrative privilages.

### Overview ###

The direct Neptune installation involves the following:

 1. Installing Python 2.7
 2. Installing dependencies (Ubuntu: `sudo neptune/install/debian_dependencies.sh`)
 3. Installing Neptune (`neptune/INSTALL.sh`)

We provide more detailed instructions below.

### Python ###

Neptune requires Python 2.7. Note that Python 2.7 is provided with many major distributions of Linux. The following may check your Python version:

```bash
python --version
```

### Dependencies ###

#### Debian-Based Installation ####

This section assumes the user has the [APT](https://help.ubuntu.com/community/AptGet/Howto) package manager. This is common to the [Ubuntu](https://en.wikipedia.org/wiki/Ubuntu_(operating_system)) operating system. However, this section should be compatible with any 64-bit Debian distribution. The following operation will automatically install Neptune's dependencies and require security privileges (sudo) to install the dependencies:

```bash
sudo neptune/install/debian_dependencies.sh
```

#### Manual Installation ####

If you cannot install the dependencies using the above script, the following dependencies must be manually installed, if necessary, by the user:

* pip
* virtualenv
* build-essential
* python-dev
* NCBI BLAST+

### Neptune ###

Neptune will be installed using pip into its own Python virtual environment. The following will install Neptune locally into the source directory and will not require security privileges:

```bash
neptune/INSTALL.sh
```

Alternatively, you may specify an install location, PREFIX, such as /usr/local/. Neptune will create the directories PREFIX/lib and PREFIX/bin. This may require security privileges:

```bash
neptune/INSTALL.sh PREFIX
```
