# GLFW OpenGL Base
Base Project structure for OpenGL + GLFW. Clone with `git clone --recursive https://github.com/BonusPlay/GLFW-OpenGL-Base.git`
and remember to build dependencies with cmake in `lib` folder. Since BASS isn't open source I didn't include it in the repo, but if you want to use it just unzip it into the `lib/bass` folder.

This project is barely a basic structure to build upon. It allows user to rapidly add new features, as all the hard work like importing assets and rendering is already done. With just a few LoC user can add 
their own shaders, models, music & other stuff.

Project also features full C++ "like" inheritance, with member fields and function overloading.

## Libraries used
- [GLAD](https://github.com/Dav1dde/glad)
- [GLFW](https://github.com/glfw/glfw)
- [GLM](https://github.com/g-truc/glm)
- [STB](https://github.com/nothings/stb)
- [assimp](https://github.com/assimp/assimp)
- [BASS](https://www.un4seen.com/)

## Usage
When user runs .exe, he will be greeted with a frozen screen (this is due to imperfection of OpenGL's single threaded nature).

![img1](images/img1.png)

User is greeted to a fully loaded 3ds Max model with textures, and a CubeMap around him.

![img2](images/img2.png)

User is able to control camera with mouse and WSAD.

![img3](images/img3.png)

User also has access to a GUI with a ~ key (some features of GUI are hidden in release build).

![img4](images/img4.png)