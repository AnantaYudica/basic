# basic
a repeatable solution
## Getting Started
## Status:
| Version|   |
:---:|---
![GitHub release (latest SemVer)](https://img.shields.io/github/v/release/AnantaYudica/basic?color=green&label=last-release&sort=semver) |  ![Unix Build Test](https://github.com/AnantaYudica/basic/workflows/Unix%20Build%20Test/badge.svg?branch=master&event=push)

 - Development
   | Branch |   |
   :----:|---
   Alpha | ![Unix Build Test](https://github.com/AnantaYudica/basic/workflows/Unix%20Build%20Test/badge.svg?branch=alpha&event=push) 
   Beta |  ![Unix Build Test](https://github.com/AnantaYudica/basic/workflows/Unix%20Build%20Test/badge.svg?branch=beta&event=push) 

## Definition
   - Directories
     | Directory | Description |
     :-----|:-----
     /cmake | CMake source project directory
     /include | Header files directory
     /test | Test main sources directory
     
## Prerequisites
   - Standard Language: __c++11__
   - __Git__: minimum version=2.14
   - __CMake__: minimum version=3.0.2
   - Linux Compiler Support:
     - GCC
  
## Build
   1. __Clone Project__
      ````
      git clone --recurse-submodules https://github.com/AnantaYudica/basic.git basic
      ````
      git clone documentation (https://git-scm.com/docs/git-clone)
   1. __Change to Project Directory__
      ````
      cd ./basic
      ````
   1. __Checkout Specific Tag__ [Optional] (Tag Example: v0.1)
      ````
      git fetch --tags
      git checkout v0.1
      ````
      git fetch documentation (https://git-scm.com/docs/git-fetch), git checkout documentation (https://git-scm.com/docs/git-checkout)
   1. __Create build Directory in Project Directory__ (Folder Example: .build)
      ````
      mkdir .build
      ````
   1. __Change to Build Directory__
      ````
      cd ./.build
      ````
   1. __Generate Project__
      - __Cmake__
        - Linux
          ````
          cmake ../cmake -G "Unix Makefiles"
          ````

        CMake documentation (https://cmake.org/cmake/help/latest/manual/cmake.1.html), CMake generator documentation (https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html)

   1. Build Project
      - Linux
        ````
        make build
        ````
   1. Testing
      - Linux
        ````
        make test
        ````
## Authors
* [Ananta Yudica](https://github.com/AnantaYudica)
## License
This project is licensed under the MIT License - see the [LICENSE.md](https://github.com/AnantaYudica/basic/blob/master/LICENSE) file for details
