**1. Tools and Environment Setup**
---
You need the following basic tools to start building Imagine.MacOS X: Xcode 9 or newer, MacPorts (http://www.macports.org)

Install Xcode on OS X 10.9 or Later
Download the latest version of Xcode from the Apple developer website or get it using the Mac App Store.
Once you have Xcode installed, open a terminal, run **xcode-select --install**, and click the Install button to install the required command line developer tools. Don't worry if you see a message telling you the software cannot be installed because it is not currently available from the Software Update Server. This usually means you already have the latest version installed. You can also get the command line tools from the Apple developer website.

Install MacPort per the instruction from MacPorts I will not cover here. Open Terminal, and sudo port selfupdate let this complete.
Now type sudo port install coreutils libtool pkgconfig gnutar autoconf  this will take a few minutes. This is need to complete the compile.
The following make variables are used by the build system: IMAGINE_PATH : Required, no default

Step 1: Open up a Terminal window (this is in your Applications/Utilities folder by default)

Step 2: Enter the follow commands: **touch ~/. profile; open ~/. Profile**

Step 3: Add the following line to the end of the file adding whatever additional directory you want in your path
	**export IMAGINE_PATH=/users/YOURNAME/Desktop/emu-ex-plus-alpha/imagine**
‘I used my desktop when building for ease of access you change your path location to the where the project is saved.’

![](https://github.com/thededman/emu-ex-plus-alpha/blob/master/fig1.png)

Step 4: Close and save the .profile

Step 5:  Close terminal and reopen.

**2. Dependencies**
---
For ports that need linking to additional static libraries (currently all except a stock Linux build), change to the "imagine/bundle/all" directory and run the specific bash script for the port to build the needed packages. 
bash makeAll-ios.sh install TAR=gnutar
 
*May have to execute this a few times to get a proper build with our errors. This may not be the case with in a native Mac OS. 
I have has issue with this version of Mac OS X as it’s virtual. 

You see this error, don’t worry run the command again.
---
autogen --writable test_endswap.def
make[1]: autogen: No such file or directory
make[1]: *** [test_endswap.c] Error 1
autogen --writable write_read_test.def
make[1]: autogen: No such file or directory
make[1]: *** [write_read_test.c] Error 1

**3. Building Imagine Framework**
---
Still in terminal in the same folder you were in for compiling IMAGINE ENGINE run this
**make -f $IMAGINE_PATH/ios-release.mk install V=1 -j4**

I run this twice to be sure of proper install, you will see this in the terminal if successful.

Installing lib & headers to /Users/YOURNAME/imagine-sdk/ios-arm64
Installing lib & headers to /Users/YOURNAME/imagine-sdk/ios-armv7 *Don't care if this one fails. This for old iPads and iPhone 4.

**4. Building EmuFramework**
---
In terminal change directory to emu-ex-plus-alpha\EmuFramework

**make -f ios-release.mk V=1 -j4** 
*run this a few time to ensure no errors. *Again I need to running from a Virtual Mac OS X.  May not happen on real mac.

run this after building - **make -f ios-release.mk install V=1 -j4** This build the emuframework and install in the IMAGINE-SDK folder.

**5. Building the Emulators**
---
Change to the directory of the emulator you want to build. For this example- I will NES.EMU
In this directory type:

**make -f ios-release.mk V=1 -j4**

This will build the executable for the emulator in save the output to target/ios-release/bin folder.
Well cover the execute file you need in the next section.

![](https://github.com/thededman/emu-ex-plus-alpha/blob/master/fig2.png)

*If you see this error don’t worry this is normal. This a signing tool for JB users. 
See http://www.saurik.com/id/8 for more information.

linking target/ios-release/bin/s9xp-arm64
Linking target/ios-release/bin/s9xp-armv7
Signing target/ios-release/bin/s9xp-arm64
make[1]: ldid: Permission denied

**6. Building for use with iOS Devices**
---
We have our executable file now, but now what? We need to add to an empty Xcode Project. For time savings, I have uploaded skeleton projects for this project.
Find the Emulator Xcode project that you want build for your device. *Free Development Account will work!.

![](https://github.com/thededman/emu-ex-plus-alpha/blob/master/fig3.png)

Continuing with NES.EMU lets open that skeleton folder.

Open the NES.EMU folder. This the framework for the NES.EMU

![](https://github.com/thededman/emu-ex-plus-alpha/blob/master/fig4.png)

This is where we will copy the INFO.plist and INFO.txt and the **NESEMU-ARM64**from the target/ios-release.
Get in to the bin folder. Notice the file name of the emulator EMULATORNAME-ARM64. This will not do.
Click on the executable, and press ENTER. Rename EMUMATORNAME only. Copy the execute to skeleton project.

![](https://github.com/thededman/emu-ex-plus-alpha/blob/master/fig5.png)

Let's go back on level in the skeleton framework and open the Xcode Project.  iOS 11 you need to be sure your copying the emulator with the ARM64 then remaming to emulator name like **NESEMU-ARM64** to **NESEMU** This is the 64bit version that will work on iOS 11

![](https://github.com/thededman/emu-ex-plus-alpha/blob/master/fig6.png)

Inside Xcode need to change the bundle identifier so something other what is listed.
Select Fix or choose your Team profile for building. 

![](https://github.com/thededman/emu-ex-plus-alpha/blob/master/fig7.png)

Plug in the iphone or iPad and select your device from the list and push the PLAY button.

![](https://github.com/thededman/emu-ex-plus-alpha/blob/master/fig8.png)

In a few moments the emulator you have compiled will launch. To ensure a proper compiled version tab LOAD GAME:

![](https://github.com/thededman/emu-ex-plus-alpha/blob/master/fig9.png)

**Roms should be uploaded with iTunes or something else (iMazing, iFunBox) in the Documents folder.**
**DO NOT ASK FOR ROMS**

Once install on the selected emulator then ROMS will show up,

![](https://github.com/thededman/emu-ex-plus-alpha/blob/master/fig10.png)

These instruction are based off of a fixed forked version for iOS. <https://github.com/palla89/emu-ex-plus-alpha> 

Hope this helps you, as if helps me as well. 

**DO NOT ASK FOR COMPILED IPA'S OR DEB FILES** The compiling the project is all in fun!

If I made any mistakes or need to change let me know. 