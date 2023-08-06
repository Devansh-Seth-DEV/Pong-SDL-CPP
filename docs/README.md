![SDL API](https://wiki.libsdl.org/static_files/logo.png)

# Simple DirectMedia Layer-SDL2

Simple DirectMedia Layer is a cross-platform development library designed to provide low level access to audio, keyboard, mouse, joystick,
and graphics hardware via OpenGL and Direct3D. It is used by video playback software,
<br>
SDL officially supports Windows, macOS, Linux, iOS, and Android. Support for other platforms may be found in the source code.
<br>
SDL is written in C, works natively with C++, and there are bindings available for several other languages, including C# and Python.
<br><br>
Official Website: [SDL](https://www.libsdl.org/)


### Abstraction of SDL
This API is a more abstract of SDL <br>
Basic app development becomes more easy using the custom API in `lib` directory
<br>

SDL2 Linux Installation
-
CMake and Make
```bash
$ sudo apt-get install cmake
$ sudo apt-get install make
```

SDL2 Developer Libraries
1. SDL2 Library
```bash
$ sudo apt-get install libsdl2-dev
```
2. SDL2 True Type Font Library
```bash
$ sudo apt-get install libsdl2-ttf-dev
```
3. SDL2 Mixer Library
```bash
$ sudo apt-get install libsdl2-mixer-dev
```
<br>

Build
-
> NOTE: Do run the commands in project directory

1. Run CMake command using `config` file
```bash
$ sh config.sh
```
2. Build project using `build` file
```bash
$ sh build.sh
```
3. Run project using `run` file
```bash
$ sh run.sh
```
