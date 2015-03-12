# emu-ex-plus-alpha
Multi-platform computer &amp; game console emulation system including supporting code (EmuFramework) and core engine (Imagine)
Building the Imagine SDK and applications is currently supported on Linux and MacOS X.
These are the instructions for the Mac OS X 10.9 and later for iOS Devices 

1. Tools and Environment Setup
-----------------------------
You need the following basic tools to start building Imagine. For platform-specific info, see the INSTALL-* file for that port.
MacOS X: Xcode 6.1 or newer, MacPorts versions of coreutils, libtool, pkgconfig and gnutar (http://www.macports.org)
The following make variables are used by the build system:
IMAGINE_PATH : Required, no default
 - The path to the root Imagine directory containing the "make/" subdirectory
IMAGINE_SDK_PATH : Optional, defaults to $(HOME)/imagine-sdk
 - When building Imagine itself, the default install path of the Imagine SDK headers & libs
 - Also used when building an Imagine-based app as the default Imagine SDK path
	a. Adding the path for Mac OS -
	Step 1: Open up a Terminal window (this is in your Applications/Utilities folder by default)

Step 2: Enter the follow commands:
touch ~/. profile; open ~/. profile

This will open the . profile file in Text Edit (the default text editor included on your system). The file allows you to customize the environment your user runs in. This profile was created when you install MacPorts.

Step 3: Add the following line to the end of the file adding whatever additional directory you want in your path:
export  IMAGINE_PATH=/users/YOURNAME/Desktop/emu-ex-plus-alpha/imagine
‘I used my desktop when building for ease of access you change your path location to the where the project is saved.’

Step 4: Close and save the .profile

Step 5:  Close terminal and reopen.

2. Dependencies
-----------------------------
For ports that need linking to additional static libraries (currently all except a stock Linux build), change to the "imagine/bundle/all" directory and run the specific bash script for the port to build the needed packages. All arguments passed to this script are passed to make directly. Extracted source & build output goes into "/tmp/imagine-bundle/$(pkgName)" but you can override the "tempDir" variable to change this. The "install" target installs the resulting files under "$(IMAGINE_SDK_PATH)" and is overridden via the "installDir" variable. Note that some packages need the GNU version of the tar utility for proper extraction.
For example, to build and install the packages needed for the iOS port, and override the name of the tar utility, use:
bash makeAll-ios.sh install TAR=gnutar 

*May have to execute this a few times to get a proper build with our errors. This may not be the case with in a native Mac OS. I have this issue with this version of Mac OS X as it’s virtual. 

You see this error, don’t worry run the command again.
-----------------------------
autogen --writable test_endswap.def
make[1]: autogen: No such file or directory
make[1]: *** [test_endswap.c] Error 1
autogen --writable write_read_test.def
make[1]: autogen: No such file or directory
make[1]: *** [write_read_test.c] Error 1

-----------------------------
3. Building Imagine Framework
-----------------------------
Use one of the makefiles in the root Imagine directory to build that specific port. Build output goes into the "build" and "lib" subdirectories of the working directory. Pass "V=1" as an override for verbose build output. For example, to build and install the debug version of the iOS ARM7/ARM64 port with verbose output and 4 compile jobs, use:

make -f $IMAGINE_PATH/ios-release.mk install V=1 -j4

I run this twice to be sure of proper install, you will see this in the terminal if successful.

Installing lib & headers to /Users/YOURNAME/imagine-sdk/ios-arm64
Installing lib & headers to /Users/YOURNAME/imagine-sdk/ios-armv7

**To use the resulting Imagine SDK with pkg-config, add that port's "lib/pkgconfig" path to the "PKG_CONFIG_PATH" environment variable. Note apps directly using Imagine's build system do this automatically by checking the "IMAGINE_SDK_PATH" environment variable.

4. Building EmuFramework
-----------------------------
Use one of the makefiles in the root Emuframework directory to build that specific port. Build output goes into the "build" and "lib" subdirectories of the working directory. Pass "V=1" as an override for verbose build output. For example, to build and install the debug version of the iOS ARM7/ARM64 port with verbose output and 4 compile jobs, use:

make -f ios-release.mk install V=1 -j4

This build the emuframework and install in the IMAGINE-SDK folder.

5. Building EMU
-----------------------------
Use one of the makefiles in the root EMULATOR directory to build that specific port. Build output goes into the "build" and "lib" subdirectories of the working directory. Pass "V=1" as an override for verbose build output. For example, to build and install the debug version of the iOS ARM7/ARM64 port with verbose output and 4 compile jobs, use:

make -f ios-release.mk V=1 -j4

This will build the executable for the emulator in save the output to target/ios-release/bin folder.
Well cover the execute file you need in the next section.
*If you see this error don’t worry this is normal. This a signing tool for JB users. 
See http://www.saurik.com/id/8 for more information.

linking target/ios-release/bin/s9xp-arm64
Linking target/ios-release/bin/s9xp-armv7
Signing target/ios-release/bin/s9xp-arm64
make[1]: ldid: Permission denied
