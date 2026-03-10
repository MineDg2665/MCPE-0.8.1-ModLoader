# MCPE 0.8.1
An attempt to decompile MCPE 0.8.1 and to make it possible to run it on different platforms. Currently it should be possible to run it on linux and windows. The project is not affiliated with mojang or microsoft.

## ModLoader

This fork includes a built-in ModLoader that allows loading mods as `.so` shared libraries at runtime.

Mods are loaded from `/games/com.mojang/mods/` directory (created automatically on first launch).

### Building a mod

Create a `.cpp` file, for example `MyMod.cpp`:

```cpp
#include <ModLoader.hpp>

class MyMod : public Mod {
public:
    const char* name() override { return "MyMod"; }
    const char* version() override { return "1.0"; }
    void onStart(Minecraft* mc) override {}
    void onTick(Minecraft* mc) override {}
};

REGISTER_MOD(MyMod)
```

Build it from the project root directory:

```
g++ -std=c++11 -fPIC -shared -I./minecraftpe/headers -I./jsoncpp/jsoncpp/include -I./RakNet/Source -I./utf8proc -I./glm -I./stb -I. -Wl,--unresolved-symbols=ignore-all -o MyMod.so MyMod.cpp -lGL
```

Place the resulting `.so` file into `games/com.mojang/mods/` inside the game data directory.

### Available mod hooks

| Method | Description |
|--------|-------------|
| `onStart(Minecraft* mc)` | Called when mod is loaded |
| `onStop()` | Called when mod is unloaded |
| `onTick(Minecraft* mc)` | Called every game tick |
| `onRender(Minecraft* mc, float delta)` | Called after level render |
| `onGUI(Minecraft* mc)` | Called after GUI render |
| `onTouch(Minecraft* mc, int action, float x, float y)` | Touch input, return true to consume |
| `onKey(Minecraft* mc, int key, bool pressed)` | Key input, return true to consume |
| `onMouseMove(Minecraft* mc, int x, int y)` | Mouse movement |
| `onMouseDown(Minecraft* mc, int button, int x, int y)` | Mouse button press |
| `onMouseUp(Minecraft* mc, int button, int x, int y)` | Mouse button release |

## Building

## Cloning the repo and extracting sounds
* Clone the repo with `--recursive` flag(or use `git submodule init` and `git submodule update` after cloning if you forgot to add it)
* Extract armeabi-v7a version of libminecraftpe.so from the apk file and put it into the same folder as `get_sound_data.py`(currently located in `./minecraftpe/`)
* Run `python get_sound_data.py` -> should generate `pcm_data.c`
* Move `pcm_data.c` to `./minecraftpe/impl/`

### Linux
Requires SDL1(`libsdl1.2-dev` and `libsdl1.2debian`), OpenAL(`libopenal-dev` and `libopenal1`), OpenGL(`libgl1-mesa-dev`), zlib (`zlib1g` and `zlib1g-dev`).
You must also have original 0.8.1 apk file to extract sounds(won't compile without them) and obtain assets(the compiled file will crash or not work properly without them).
* ```
  mkdir build
  cd build
  cmake .. -DJSONCPP_WITH_TESTS=OFF -DJSONCPP_WITH_POST_BUILD_UNITTEST=OFF
  make
  ```
* the output should be `minecraftpe/build/minecraftpe08decomp`

### Other OSes
Currently the project should also support windows and android(currently has some bugs).

Windows version does not require OpenAL(it uses DirectSound instead). It should be possible to cross compile this project for windows by using something like
```
cmake .. -DJSONCPP_WITH_TESTS=OFF -DJSONCPP_WITH_POST_BUILD_UNITTEST=OFF -DCMAKE_SYSTEM_NAME=Windows -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++ -DCMAKE_EXE_LINKER_FLAGS="${CMAKE_EXE_LINKER_FLAGS} -static" -DCMAKE_FIND_ROOT_PATH_MODE_PROGRAM=NEVER -DCMAKE_FIND_ROOT_PATH_MODE_LIBRARY=ONLY -DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE=ONLY -DSDL_LIBRARY=/usr/x86_64-w64-mingw32/lib/SDL.dll -DZLIB_LIBRARY=/usr/x86_64-w64-mingw32/lib/zlib1.dll -DCMAKE_FIND_ROOT_PATH=/usr/x86_64-w64-mingw32/
```
(def should be simplifed later)

**Building on windows was not tested!**


Android version is still in development and doesn't really have any building instructions. You have to obtain sources of 0.8.1 apk file by using some decompiler(like jadx), import them into android studio project ~~(or epic eclipse adt <3)~~ and add this project into the created project. You might have to modify raknet or some other library for it to compile successfully.


### Running
* extract `assets` from real MCPE 0.8.1 apk into the folder you're running the executable from
* run compiled executable

## Some additional info:
* JSON library that was probably used by Mojang: https://chromium.googlesource.com/external/jsoncpp/+/6921bf1feef6f1fb83935ae3943f07753488311d/jsoncpp
* RakNet: https://web.archive.org/web/20260101222408if_/http://www.raknet.com/raknet/downloads/RakNet_PC-4.036.zip (might be some other version, probably modifed by mojang in 0.1.x)
* GZIP stuff - zlib 1.2.3, based on https://zlib.net/zpipe.c
* https://github.com/nothings/stb/
* GLM - commit before https://github.com/g-truc/glm/commit/2b747cbbadfd3af39b443e88902f1c98bd231083 and -DGLM_FORCE_RADIANS <?>
