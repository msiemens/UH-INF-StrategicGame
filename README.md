# UH-INF-StrategicGame

[![Build Status](https://travis-ci.org/msiemens/UH-INF-StrategicGame.png?branch=master)](https://travis-ci.org/msiemens/UH-INF-StrategicGame)

## Abstract:

This is strategic game implemented in C++. This project is part of informatics lecture project at Leibniz University Hannover (Germany).

## How to hack on this:

### Software dependencies

1. **Install MinGW**. It provides the compiler and the build toolchain needed to compile this project. You'll find it at http://downloads.sourceforge.net/project/mingw/Installer/mingw-get-inst/mingw-get-inst-20120426/mingw-get-inst-20120426.exe. Install it using this options:
    1. "Download latest repository catalogues"
    2. "Accept"
    3. The path where you want MinGW to live
    4. The default value
    5. "C Compiler", "C++ Compiler" and further below: "MinGW Developer Toolkit"
    6. Install the Boost Libraries. Download them from http://sourceforge.net/projects/boost/files/boost/1.52.0/boost_1_52_0.zip/download and unpack it. Then move the directory "boost" from the extraced directory to "<MinGW-Root>/include/".
2. **Install CMake**. This is the build system. It makes it easier to compile all the files needed. The download is located at http://www.cmake.org/files/v2.8/cmake-2.8.9-win32-x86.exe and more information about CMake is at http://en.wikipedia.org/wiki/CMake. Install it with default options.
3. **Install Eclipse CDT**. Download it from http://www.eclipse.org/downloads/download.php?file=/technology/epp/downloads/release/juno/SR1/eclipse-cpp-juno-SR1-win32.zip and unpack it somewhere where you'll find it.

### Setup for Eclipse

0. **Open Eclipse**.
1. **Install Git plugin**.
    1. Go to "Help > Install new software...".
    2. Enter "http://download.eclipse.org/egit/updates" into the "Work with" field.
    3. Select all checkboxes in the install field.
    4. Select "Next" until the installation is done.
    5. Restart Eclipse.
2. **Import the GitHub repo/source project**.
    1. Go to "File > Import...".
    2. Select "Git > Projects from Git".
    3. Select "URI".
    4. Enter "https://github.com/msiemens/UH-INF-StrategicGame.git" into the URI field, your GitHub username and password into the corresponding fields and select "Next".
    5. Select "master" only.
    6. Select "Next".
    7. Select "Next".
    8. Select the project and go to "Finish".
3. **Generate build files with CMake**.
    1. Open the directory where the cloned repository is.
    2. Create a new directory called "<name-of-repo-dir>.build". 
    3. Start CMake (cmake-gui).
    4. In "source code", put the path of the cloned repository and in "build" put the directory created in 3.2.
    5. Click "Configure".
    6. In the new window, select "Eclipse CDT4 - MinGW Makefiles" and click "Finish".
    7. Click "Configure" again.
    8. Click "Configure" again.
    9. Click "Generate".
4. **Import build project into Eclipse**.
    1. Open Eclipse again.
    2. Go to "File > Import...".
    3. Select "Existings Projects into Workspace" and click "Next".
    4. Into "root directory" enter the "build" path (as set in 2.6), select your project and click "Finish".
    5. The build project is now in the "Project Explorer".
5. **Happy coding :)**
    - You now have two new projects in Eclipse:
        - The source project is where you edit the sources etc.
        - The build project is where you can compile the project and run executables.
    - To run an exectuable, please contact me ;)
    - For more information on Git for Eclipse, please check out http://www.vogella.com/articles/EGit/article.html.

## Code Conventions

See: http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml#Naming (but conventions are open for discussion here).

## Other Conventions

- `master` branch is always clean and should compile without errors
