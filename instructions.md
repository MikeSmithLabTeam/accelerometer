# Getting setup with the RP2040-LCD-1.28 accelerometer code

You're going to need to set up a bunch of the toolchain. Things like the pico-sdk, cmake, gcc compiler etc. Sadly I didn't document this when I did it. I've added the pdf:
"How to setup the Raspberry PiPico C_C++..." which I used. I seem to remember there were some steps that needed more googling. If you repeat the setup please come back here and write it up! This should enable you to get all the build tools setup.

The picosdk when installed comes with a bunch of examples called pico-examples. I would just copy the relevant files from here into that directory. I have written all my code for the accelerometer inside RP2040-LCD-1.28. I have also modified the top level CMakeLists.txt so that it only builds the bits we're interested in and not the millions of other examples. 

I think easiest way to build everything is to delete any existing build directory and recreate it. Vscode seems to hang onto some filehandle which means you often need to start Vscode to delete the build directory.

In Pico-examples:
1. mkdir build
2. cd build
3. cmake -G "MinGW Makefiles" ..
4. cd RP2040-LCD-1.28
5. make

These steps will produce a main.uf2 in build > RP2040-LCD-1.28

Plug the RP2040... into the computer with a cable but hold the boot button on the back at the same time. This should then mount like a usb drive and show up in file explorer.

Drag and drop the uf2 file onto the device and it should automatically reboot and start running the code.




