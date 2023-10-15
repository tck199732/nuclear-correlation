<a href="https://www.cplusplus.com/"><img src="https://img.shields.io/badge/C++-v17-005697.svg?style=flat&logo=c%2B%2B" alt="C++"></a>
<a href="https://root.cern/"><img src="https://img.shields.io/badge/ROOT-6.28.00-blue.svg?style=flat&logo=data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAYAAAAf8/9hAAAAGXRFWHRTb2Z0d2FyZQBBZG9iZSBJbWFnZVJlYWR5ccllPAAAA2RpVFh0WE1MOmNvbS5hZG9iZS54bXAAAAAAADw/eHBhY2tldCBiZWdpbj0i77u/IiBpZD0iVzVNME1wQ2VoaUh6cmVTek5UY3prYzlkIj8+IDx4OnhtcG1ldGEgeG1sbnM6eD0iYWRvYmU6bnM6bWV0YS8iIHg6eG1wdGs9IkFkb2JlIFhNUCBDb3JlIDUuMC1jMDYwIDYxLjEzNDc3NywgMjAxMC8wMi8xMi0xNzozMjowMCAgICAgICAgIj4gPHJkZjpSREYgeG1sbnM6cmRmPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5LzAyLzIyLXJkZi1zeW50YXgtbnMjIj4gPHJkZjpEZXNjcmlwdGlvbiByZGY6YWJvdXQ9IiIgeG1sbnM6eG1wTU09Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC9tbS8iIHhtbG5zOnN0UmVmPSJodHRwOi8vbnMuYWRvYmUuY29tL3hhcC8xLjAvc1R5cGUvUmVzb3VyY2VSZWYjIiB4bWxuczp4bXA9Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC8iIHhtcE1NOk9yaWdpbmFsRG9jdW1lbnRJRD0ieG1wLmRpZDo5MEREM0ZCMTE3QTVFMzExODVDNDhENDcyNTVBNzdGNSIgeG1wTU06RG9jdW1lbnRJRD0ieG1wLmRpZDo0MTY3Q0YzNEE1MUYxMUUzQjJFNDk3MEU0NTA2N0U0MiIgeG1wTU06SW5zdGFuY2VJRD0ieG1wLmlpZDo0MTY3Q0YzM0E1MUYxMUUzQjJFNDk3MEU0NTA2N0U0MiIgeG1wOkNyZWF0b3JUb29sPSJBZG9iZSBQaG90b3Nob3AgQ1M1IFdpbmRvd3MiPiA8eG1wTU06RGVyaXZlZEZyb20gc3RSZWY6aW5zdGFuY2VJRD0ieG1wLmlpZDo5MEREM0ZCMTE3QTVFMzExODVDNDhENDcyNTVBNzdGNSIgc3RSZWY6ZG9jdW1lbnRJRD0ieG1wLmRpZDo5MEREM0ZCMTE3QTVFMzExODVDNDhENDcyNTVBNzdGNSIvPiA8L3JkZjpEZXNjcmlwdGlvbj4gPC9yZGY6UkRGPiA8L3g6eG1wbWV0YT4gPD94cGFja2V0IGVuZD0iciI/PuK5HSIAAAG3SURBVHjahJM5SwNREMdn3yabGFAUj8JCjSgGBbGwEdLaimIh1kIag/gFrLQSxE/gF1AbsQo2GmyUoI0nYqLGI+TSnJvNbt5zXrIJ6+Zw4Lfszpv57wwzT2CMgcmcyAoyi4zpvkfkBNlDQn+iuYABD5JhzS2jx9RyBL0CETlAFszlPCkaFGilShsR8pIASlKjIX9OmVnvbS9a9LjtRsncll7ikNBo+b3bQhz9VtEhgtA17ZD20TXPyxhBlEb1RtUSG7j5YNf5+mONMo3nElTxIlKjv98WVBAFAJfNWneGft62lwu4oYndocCgZAE7EZqFuAl2N2T08H5jes8PKNDo7wYbINkS7ah++dIFmH2OwmYkVavAZbe0EgAS0aiaKVFYe/8GTzgJw1jyUUqG06wCwaIG4/aWFbyR45TsnwvFoVMkcDbaB4fOHphqk8CLgiUG/7VwDsuh+GQcx2W0y5xSHt/E/VeLpayMsbyOvrQcMJ+uvCbYYjDWSmCnvMX8sRtNS1d5JWw8fS6obOPzp1nyESLWBKrgRFZVymTjJv53mcy3keNEtpALTE8rlMooGtB9TnP8rwADAN7Z882fu9StAAAAAElFTkSuQmCC" alt="ROOT"></a>
<a href="https://docs.conda.io/projects/conda/en/stable/user-guide/index.html"><img src="https://img.shields.io/badge/anaconda-v4.14.0-green.svg?style=flat&logo=anaconda"></a>
<a href="https://gitmoji.dev/"><img src="https://img.shields.io/badge/gitmoji-%20😜%20😍-FFDD67.svg?style=flat-square" alt="Gitmoji"></a>
<a href="https://cmake.org/"><img src="https://img.shields.io/badge/CMake-3.26.4-blue.svg" alt="Cmake"></a>

# NuclearCorrelation
This repository is developed with ROOT version `6.28.00`, `cpp17`, using `cmake v3.26.4`. The purpose of this repo is to calculate **two-particle correlation function** for both experimental data and simulated data using the `StHbt` framework developed years ago. The main outputs of the program are the numerator and denominator of the correlation. 

### Why another repository for StHbt? 
- The current version compilate the code with `cmake` for better readability and tractability.
- The legacy StHbt code was written years ago using `cpp11` and most code are designed for high-energy community in which many features are not required in low-energy nuclear physics. Some old mathematical libraries are also obsolete. The current version simplifies the code with modern cpp.
- ROOT dictionary are not generated to simplify the process as this features seems to be not that neccessary. Also, unless ROOT version `6.29+` is used, `rootcling` conflicts with the use of `std::filesystem`, see [here](https://root-forum.cern.ch/t/rootcling-with-std-filesystem/55388).


## **Content**
 - [Installation](#1-installation)
 - [Directory](#2-directory)
 - [Usage](#3-How-to-use)
 - [Further-Reading](#4-Further-Reading)

### 1. Installation
- clone the repo.
    ```{bash}
    git clone https://github.com/tck199732/NuclearCorrelation.git
    ```
- if have not done, install anaconda3 (https://docs.anaconda.com/anaconda/install/linux/). Activate the base environment, 
    ```
    source $install_dir/bin/activate
    ```
- create the environment
    ```
    conda env create -f environment.yml --prefix ./env_sthbt
    ```

### 2. Directory
- [**`assets/`**](assets/) : contains useful data such as ame amss table and some sample data for testing purpose.
- [**`dev`**](dev/) : base class and backbone codes for correlation analysis using event-mixing method. User shall not modify in most scenario.
- [**`custom`**](custom/) : all user-defined codes for customizing event reader, kinematic cuts and specified forms of correlation functions.
- [**`exec`**](exec/) : contain main scripts to run the program.

### 3. Usage

### 4. Further-Reading
 - [`Two-Proton CF paper`](https://link.aps.org/accepted/10.1103/PhysRevC.85.014606) : uses data from experiment E03045, two-proton CF exhibits dependence on momentum. 
 - [`Zbigniew's phd thesis`](https://inspirehep.net/files/455e02c0dc66388a4e86f2874ecc8023) : Check out chapter 5 for details in spherical-harmonincs decompoistion of Correlation Function.
 - [`Spherical-Harmoncis Components Paper`](https://journals.aps.org/prc/abstract/10.1103/PhysRevC.80.064911) : Directly sample 1D numerator and denominator weighted with $Y_l^m$, which alse used to extract components of CF expanded with $Y_l^m$.
 - [`Theory on the spherical moments`](https://journals.aps.org/prc/abstract/10.1103/PhysRevC.81.064906)



