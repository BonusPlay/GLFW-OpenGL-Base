# GLFW OpenGL Base
Base Project structure for OpenGL + GLFW. Clone with
`git clone --recursive https://github.com/BonusPlay/GLFW-OpenGL-Base.git`
and remember to build dependencies with cmake in `lib` folder. Since BASS isn't open source I didn't include it in the repo, but if you want to use it just unzip it into the `lib/bass` folder. Press ` (tilde) in game to view UI. Feel free to use/contribute.

## Features
- [x] Multiplatform (Windows, Linux, macOS)
- [x] GameStates
- [x] Music
- [x] Camera
- [x] 3d Models
- [x] Shader
- [x] dear ImGui ❤️
- [x] Fontawesome, Material Design icons
- [ ] Multithreading
- [ ] Tests
- [ ] x64 configuration
- [ ] Dictionary for resources (unsure yet)

## Libraries used
- [GLAD](https://github.com/Dav1dde/glad)
- [GLFW](https://github.com/glfw/glfw)
- [GLM](https://github.com/g-truc/glm)
- [STB](https://github.com/nothings/stb)
- [assimp](https://github.com/assimp/assimp)
- [imgui](https://github.com/ocornut/imgui)
- [BASS](https://www.un4seen.com/)
- Icon fonts: [Font Awesome](https://github.com/FortAwesome/Font-Awesome), [Material Design Icons](https://github.com/google/material-design-icons), [Kenney](http://kenney.nl/assets/game-icons)

## Multithreaded architecture
Application is divided into 3 threads:
- main - the only thread that can invoke some GLFW functions (like [`glfwGetCursorPos`](http://www.glfw.org/docs/latest/group__input.html#ga01d37b6c40133676b9cea60ca1d7c0cc)).
- backend - updates world independently from other threads
- frontend - renders the world it has *as it is* (that means that world can update mid-render). This is also the only thread that can run OpenGL functions (since it has OpenGL context)

## FAQ
**Q: Why global `unique_ptr<Game>`?**

*I know that's a dirty solution and I could (maybe should) use Singleton pattern design, but this solution is cheap and it works. I just don't like moving mountains just to follow some guidlines, if there is much easier way to do something, with little to no cost. Feel free to change it if you don't like it.*

**Q: Did you write `imgui_impl` by yourself?**

*No, I modified and updated [this](https://github.com/ocornut/imgui/tree/master/examples/opengl3_example) to use my classes and add some other stuff.*

**Q: Did you write all of the OpenGL classes alone?**

*No, I used a lot of code from [this tutorial](https://learnopengl.com) (which is great tutorial that I recommend it to anyone that wants to learn OpenGL) and packed it into normal classes.*

**Q: Why BASS instead of OpenAL/any other audio lib?**

It's **super** easy to use and get's job done in fewest lines of code (for example OpenAL's example is over 350 lines of code). However, if you want to use your own audio lib it should be pretty easy to change.*

**Q: Why do you use precompiled headers and why do you not include them in your `.cpp` files?**

*Using precompiled headers speeds up compile time. I don't need to include them thanks to `ForceInclude` option in project settings.*

**Q: Why do you say** ***"I reserve the right to revoke this use of this license at any time, for any reason, and at the sole discretion of mine."*** **in the license?**

*Just as a backup to to punish anyone that breaks the license.*