# Stack

- GLFW
    [https://www.glfw.org]
- OpenGL
    [https://learnopengl.com]
- glm - OpenGL Mathematics
    [https://glm.g-truc.net/0.9.9/index.html]
- WebGL
    [https://webglfundamentals.org]
    [https://learnwebgl.brown37.net/index.html]

# GLFW - Graphics Library Framework
> GLFW integration into project git
```bash
git remote add glfw https://github.com/glfw/glfw.git
git subtree add --prefix=external/glfw glfw master --squash
```
> Latest version
```bash
git subtree pull --prefix=external/glfw glfw master --squash
```

> Cmake
```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

## GLAD
> generate Glad
- [https://glad.dav1d.de]
- Specification: OpenGL
- Profile: Core
- Version: <version>
- Generate
```bash
unzip glad.zip
mv glad external/
cd external/glad && touch CMakeLists.txt
```
- edit main CMakeLists.txt
```
add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)
```

# GLM
```bash

```

### Coordinate System
- `Local space` or `Object space` --> __model matrix__ -->
- `World space` --> __view matrix__ -->
- `View space` or `Eye space` --> __projection matrix__ -->
- `Clip space` --> __viewport transform__ -->
- `Screen space`

# RapidJSON







## OpenGL on Ubuntu

> GLFW GLEW

```bash
sudo apt update
sudo apt install build-essential cmake xorg-dev
```
> GLFW
- [https://www.glfw.org/download.html]
- source package
- unzip and cd into dir

```bash
cmake -G "Unix Makefiles"
make
sudo make install
```

> Unbuntu install

```bash
sudo apt-get install libx11-dev libglu1-mesa-dev freeglut3-dev libglew2.2 libglew-dev libglu1-mesa libgl1-mesa-glx libgl1-mesa-dev libglfw3-dev libglfw3
```

> ArchLinux install

```bash
sudo pacman -S glfw
```

> Compiling

```bash
gcc source.c -o executable -Wall -lGl -lGLU -lglut -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor


g++ source.cpp -o executable -std=c++11 -Wall -lGl -lGLU -lglut -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor
```
