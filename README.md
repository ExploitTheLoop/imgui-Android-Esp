# PUBG Android ImGUI
Pubg android esp external with ImGUI.
![](https://cdn.discordapp.com/attachments/984530721806884955/1154454620572242060/photo1695313208.jpeg)

## Features
- Built with [ImGUI](https://github.com/ocornut/imgui).

## Coming Soon
- None

## Requirements
The following dependencies are required to build the library from source.
- [NDK Android](https://developer.android.com/ndk).
- [APK Easy Tools](https://forum.xda-developers.com/android/software-hacking/tool-apk-easy-tool-v1-02-windows-gui-t3333960).
- Any text editor. We use [Notepad++](https://notepad-plus-plus.org/).

For AIDE users (I'm not sure if this works 100%).
- [AIDE CMods](https://secufiles.com/nE9J/AIDE_CMODs_3.2.200108.apk).
- [NDK AIDE for arm32](https://www.mediafire.com/file/62l4gcxqsqtxy20/ndk_arm.tar.gz/file).
- [NDK AIDE for arm64](https://www.mediafire.com/file/w56tbt9pmqxzmpu/ndk_arm64.tar.gz/file).
- [APK Tool M](https://maximoff.su/apktool)

There are many tutorials for installing on youtube, Attention if your android doesn't support arm then it won't work. one of them [AIDE CMods tutorial](https://youtu.be/VYvKEFHSgkg)

## Building the source
`ndk-build`:
```shell
git clone https://github.com/ZTzTopia/GTInternalAndroid
cd GrowtopiaImGui
ndk-build
```

You need [ninja](https://ninja-build.org/) build system to use ninja cmake generator.

`cmake`:
```shell
mkdir build
cd build
cmake -GNinja -DCMAKE_MAKE_PROGRAM=/path/to/ninja.exe -DCMAKE_ANDROID_NDK=/path/to/android-ndk \
  -DCMAKE_TOOLCHAIN_FILE=toolchains/android.cmake ..
cmake --build .
```
