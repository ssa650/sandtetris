# Sand Tetris C++ project - ENSC-151

Sand Tetris, also known as Sandtrix or Setris, is a puzzle game that combines elements of Tetris with a unique twist: when the blocks land, they turn into sand and crumble. The objective is to align blocks of the same color to form continuous lines, which then disappear, earning points for the player.


## Requirements 

Before building the project, make sure you have the following installed:

- **CMake minimum 3.2.8** — for generating build files
- **Git latest** - CMake installs raylib.h directly into our project through git so make sure you have git installed on your machine 
- **raylib.h installed in project directory** - there is no need to install raylib.h onto your machine as CMake is instructed to do it for us

    Definitely check out the [raylib.h Docs][raylib-docs], [CMake Docs][cmake-docs], and [install git][git-install] if you havent yet!

## Installation

```bash
#MacOs
brew install cmake

#Arch Linux 🐧
sudo pacman -S cmake

#Windows 10/11
choco install cmake
```
MacOs [homebrew][brew-install] package manager installation guide 

Windows 10/11 [chocolatey](https://chocolatey.org/install) package manager installation guide

**You will also need git installed on your machine because of the way CMake uses raylib.h as a dependency**


## CMake for our project


### What does CMake do

- CMake is a build system generator, CMake doesnt compile code itself, but it creates build files for our compiler to use
- CMake handles compiling files and linking dependencies into a executable by generating correct build commands for your systems compiler 
- CMake requires a file called `CMakeLists.txt` for build instructions, which contains all the build instructions
- please go through [CMakeLists.txt](sandtetris/CMakeLists.txt) to learn how we give CMake build instructions

### Why CMake benefits this project 

- CMake allows us to easily compile multiple source files so you dont have to deal with compiler commands
- CMake allows us to compile files incrementally meaning only the files that changed are recompiled instead of the whole project
- CMake also keeps the project orginized and portable allowing our code to build seamlessly on every OS

### Basic CMake commands 

- CMake stores build files along with the executable file in the build directory
- the command: `cmake -S . -B build -G "MinGW Makefiles"` gets CMake to replace or make a new build directory and then make all the build files inside of it
- to properly execute this command you must `cd` to the root project directory `/sandtetris/` where CMake can both find the build instructions and make the build directory
- you need to replace the build directory with the `cmake -S . -B build -G "MinGW Makefiles` command if 
    - the build files are for a different OS
    - you changed compilers or build systems
    - you made a change to `CMakeLists.txt`
    - you chnaged dependencies
    - you added or removed source files
    - you changed the c++ standard
    - the build files are for a different CPU architecture
    - or the `compile_commands.json` file doesnt belong to you (build might still work but your code editor integration will break)

**I have set up gitignore to ignore all build files, SFML build files, vscode files etc so you dont have to worry about pushing your build folder**

- So after you replace the build directory and build files with the `cmake -S . -B build -G "MinGW Makefiles` command everything should compile and work perfectly on your machine
- the command: `cmake -S . -B build -G "MinGW Makefiles` only gets CMake to create the appropriate files for your environment
- once you have the proper build files set up you can use the command: `cmake --build build` to create an executable file
- you must also run the `cmake --build build` command in the root directory of the project 
- the newly created executable file will appear in the build directory
- in most situations you will use the `cmake --build build` command as it only compiles the files that have been changed making the build process fast and efficient    




[brew-install]: https://brew.sh/
[cmake-install]: https://cmake.org/download/
[git-install]: https://git-scm.com/install/

[raylib-docs]: https://www.raylib.com/index.html
[cmake-docs]: https://cmake.org/cmake/help/latest/




