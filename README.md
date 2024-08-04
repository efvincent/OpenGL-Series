# Cherno's OpenGL Series
Following along with the series. Each folder is labeled epNN corresponding roughly to which
episode the project represents. Roughly because often there are multiple episodes covered
by a single episode project.

## Prerequisites
C++ Standard 20 is required for compilation. I'm testing with GCC 13. 

## VCPKG
See [documentation](https://learn.microsoft.com/en-us/vcpkg/get_started/overview) for vcpkg to get started.
You'll need to install vcpkg and the packages for imgui, opengl, glew, glut, glfw3, and glm.

Main libraries/packages:
* OpenGL
* [glfw3](https://www.glfw.org/)
* [glew](https://glew.sourceforge.net/)
* glad

### GLFW
```bash
$ sudo apt install libglfw-dev
```

### ImGui
```bash
$ vcpkg install imgui
```
## Building
This project uses CMake to set the build system.

## Notes



