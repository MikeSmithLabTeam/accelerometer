## Using and uploading the accelerometer

If you just want to load the code onto a new accelerometer then press and hold the boot button on the back and plug it in to computer via usb.
This will mount as an external drive in file explorer. Find the main.uf2 file which is in the top level of the accelerometer repo. Drag and drop this
onto the device. It will reboot and you are good to go.

The calibrations for each accelerometer are hardcoded into the code so its important not to muddle them up. The holders have a number. The uf2 files are in a folder with the accelerometer numbers.

## Getting setup and building the RP2040-LCD-1.28 accelerometer code from source

You're going to need to set up a bunch of the toolchain. Things like the pico-sdk, cmake, gcc compiler etc. Sadly I didn't document this when I did it. I've added the pdf:
"How to setup the Raspberry PiPico C_C++..." which I used. I didn't follow the advice to install python3 globally. Instead create a conda environment "conda create -n accelerometer python=3.10"

The picosdk when installed comes with a bunch of examples called pico-examples. I would just copy the relevant files from here into that directory. I have written all my code for the accelerometer inside RP2040-LCD-1.28. I have also modified the top level CMakeLists.txt so that it only builds the bits we're interested in and not the millions of other examples. 

I think easiest way to build everything is to delete any existing build directory and recreate it. Vscode seems to hang onto some filehandle which means you often need to start Vscode to delete the build directory.

**Make sure you run the command in cmd which is partially obscured in the pdf**

echo mingw32-make %* > C:\VSARM\mingw\mingw32\bin\make.bat

In Pico-examples:
1. mkdir build
2. cd build
3. conda activate accelerometer
4. cmake -G "MinGW Makefiles" ..
5. cd RP2040-LCD-1.28
6. make

These steps will produce a main.uf2 in build > RP2040-LCD-1.28

Plug the RP2040... into the computer with a cable but hold the boot button on the back at the same time. This should then mount like a usb drive and show up in file explorer.

Drag and drop the uf2 file onto the device and it should automatically reboot and start running the code.

## Modifying the code

The CMakeLists.txt has a list of subdirectories to add. Inside the RP2040-LCD-1.28 folder is a ReadmeEN which has some instructions. You can tweak things like the accelerometer range, access gyros and magnetometers. I'd look at the original example main.c code in RP2040-LCD-1.28. I'd then cut together what you want with the main.c code in RP2040-LCD-1.28.



