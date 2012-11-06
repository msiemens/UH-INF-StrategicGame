# UH-INF-StrategicGame

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
2. **Install CMake**. This is the build system. It makes it easier to compile all the files needed. The download is located at http://www.cmake.org/files/v2.8/cmake-2.8.9-win32-x86.exe and more information about CMake is at http://en.wikipedia.org/wiki/CMake. Install it with default options.
3. **Install Eclipse CDT**. Download it from http://www.eclipse.org/downloads/download.php?file=/technology/epp/downloads/release/juno/SR1/eclipse-cpp-juno-SR1-win32.zip and unpack it somewhere where you'll find it.

### Setup for Eclipse

1. **Open Eclipse**.
1. **Install Git plugin**.
    1. Go to "Help > Install new software...".
    2. Enter "http://download.eclipse.org/egit/updates" into the "Work with" field.
    3. Select all checkboxes in the install field.
    4. Select "Next" until the installation is done.
    5. Restart Eclipse.
2. **Clone the GitHub repo**.
    1. Go to "Window > Open Perspective > Other...".
    2. In the new window, select "Git Repository Exploring"
    3. Click the button "Clone a Git repository" (see: http://m-siemens.de/other/screenshots/2012-11-06_10-06-38.png)
    4. Into "URI", enter https://github.com/msiemens/UH-INF-StrategicGame.git and enter your GitHub account data into "Authentication" (select "Store in Secure Store" to store the password so you don't have to re-enter it). Click "Next".
    5. Leave the defaults and click "Next".
    6. Leave defaults (or set a custom destination directory) and click "Finish".
3. **Generate project files with CMake**.
    1. Open the directory where you cloned the repository into (as set in 2.6).
    2. Create a new directory called "<name-of-repo-dir>.build". 
    3. Start CMake (cmake-gui).
    4. In "source code", put the path of the repository (as set in 2.6) and in "build" put the directory created in 3.2.
    5. Click "Configure".
    6. In the new window, select "Eclipse CDT4 - MinGW Makefiles" and click "Finish".
    7. Click "Configure" again.
    8. Click "Configure" again.
    9. Click "Generate".
4. **Import project into Eclipse**.
    1. Open Eclipse again.
    2. Go to "File > Import...".
    3. Select "Existings Projects into Workspace" and click "Next".
    4. Into "root directory" enter the "build" path (as set in 2.6), select your project and click "Finish".
    5. If not already done, open the "C/C++ Perspective" (see http://m-siemens.de/other/screenshots/2012-11-06_10-44-09.png). The project is now in the "Project Explorer".
5. **Happy coding :)**
    - The source code is at "[Source Directory]".
    - To build the project, select "Build all" (see http://m-siemens.de/other/screenshots/2012-11-06_10-45-36.png).
    - To run an exectuable, please contact me ;)
    - For more information on Git for Eclipse, please check out http://www.vogella.com/articles/EGit/article.html.

## Code Conventions