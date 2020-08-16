# Ivorium example
Example project for ivorium game development framework.

# Fetch
```sh
# clone repository
git clone https://github.com/ivorne/iv_example.git
cd iv_example

# clone submodules
git submodule update --init --recursive
```

# Dependencies and building
All platforms require CMake >=3.10.

Not all of these platforms were tested, any fixes would be welcome.

#### Resources
Resource compilation process has some extra dependencies listed in README.md of [ivorne/iv_rctools](https://github.com/ivorne/iv_rctools).

Resource compilation is skipped when target platform is different from host platform.
When cross-compiling (mobile platforms, Emscripten, Mingw on Linux), copy `data` directory from your natively built project to directory with your cross-compiling project.

#### Linux
  - GCC / Clang with c++17 support
  - Xorg development libraries `xorg-dev` or Wayland development libraries `libwayland-dev`
  - ALSA development libraries `libasound2-dev`
  - Build with makefiles:
      ```sh
      mkdir build
      cd build
      cmake ..
      cmake --build .
      ```
  - or generate CodeBlocks project:
      ```sh
      mkdir project_cb
      cd project_cb
      cmake -G "CodeBlocks - Unix Makefiles" ..
      ```
  - or use different generator: [cmake-generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html)

#### Linux / MinGW
  - mingw-w64
  - [toolchain.cmake](https://gitlab.kitware.com/cmake/community/-/wikis/doc/cmake/cross_compiling/Mingw) file
  - Build with makefiles:
      ```sh
      mkdir build_mingw
      cd build_mingw
      cmake -DCMAKE_TOOLCHAIN_FILE="../Toolchain_mingw32.cmake" ..
      cmake --build .
      ```

#### Windows
  - Visual Studio
  - Generate [Visual Studio project](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#visual-studio-generators):
      ```sh
      mkdir project_vs
      cd project_vs
      cmake -G "Visual Studio 16 2019" ..
      ```
   - or use [CMake GUI](https://cmake.org/runningcmake/) to generate projects.
  
#### Windows / MinGW
  - [mingw-w64](http://mingw-w64.yaxm.org/doku.php/download/mingw-builds)
  - Build with makefiles:
      ```sh
      mkdir build
      cd build
      cmake -G "MinGW Makefiles .."
      mingw32-make
      ```
  - or generate CodeBlocks project:
      ```sh
      mkdir project_cb
      cd project_cb
      cmake -G "CodeBlocks - MinGW Makefiles" ..
      ```
  - or use different generator: [cmake-generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html)

#### MacOS
  - Xcode
  - Generate Xcode project:
      ```sh
      mkdir project_xcode
      cd project_xcode
      cmake -G "Xcode" ..
      ```
  
#### Android
  - Android Studio and [NDK](https://developer.android.com/ndk)
  - GLFM instructions: [brackeen/glfm#android-studio](https://github.com/brackeen/glfm#android-studio)
  
#### iOS
  - Xcode
  - Generate Xcode project:
      ```sh
      mkdir project_ios
      cd project_ios
      cmake -GXcode -DCMAKE_SYSTEM_NAME=iOS ..
      ```

#### Emscripten (web)
  - [Emscripten](https://emscripten.org/docs/getting_started/downloads.html)
  - Build with makefiles:
      ```sh
      EMSCRIPTEN_ROOT_PATH=~/projects/emsdk/upstream/emscripten
      mkdir build_emscripten
      cd build_emscripten
      cmake -DCMAKE_TOOLCHAIN_FILE=$EMSCRIPTEN_ROOT_PATH/cmake/Modules/Platform/Emscripten.cmake -DCMAKE_BUILD_TYPE=MinSizeRel ..
      cmake --build .
      ```
  - Run locally:
      ```sh
      python3 -m http.server 8080
      ```
