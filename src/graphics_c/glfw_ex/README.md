# GLFW
> GLFW integration into project git
```bash
git remote add glfw https://github.com/glfw/glfw.git
git subtree add --prefix=external/glfw glfw master --squash
```
> Latest version
```bash
git subtree pull --prefix=external/glfw glfw master --squash

```






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
