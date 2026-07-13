# Project Pegasus

Pegasus is a basic ponytown map editor for exporting, importing, and previewing ponytown maps in the open source tiled .tmx format. Entierly offline and on your own computer.

I started this project as a senior in high school. It's based off of the C++ SFML tutorials provided by [Suraj Sharma](www.youtube.com/watch?v=IdKZpv6xqdw&list=PL6xSOsbVA1ebkU66okpi-KViAO8_9DJKg). LLM tools have NOT been used for any portion of this project, nor will they. This has been a hobby project for nearly a decade now ( as the lack of organization probably shows ) 

# Why? 
Just for fun really :P 
But also, I've always wanted the ability to decorate ponytown islands even while offline. And this project has been a pretty fun way to learn how to use SFML

# Assets and Art 
The images used are sourced from a publicly accessible [fork of ponytown](https://github.com/drewdru/ponyTown), which are released under creative commons 4.0 ( If you are an artist or illustrator for ponytown and you DONT want your assets used here, please open a new issue or contact me )


# Building 

## Dependencies 
This project fetches and builds SFML 3.0 from source, so you need the dependencies for the following SFML modules installed 

SFML
(SFML::Window, SFML::Graphics, SFML::System) 
### Linux 

#### Fedora / RedHat 
`sudo dnf install gcc-c++ make cmake libX11-devel libXrandr-devel libXcursor-devel libXi-devel systemd-devel mesa-libGLU-devel libvorbis-devel openal-soft-devel freetype-devel libgudev-devel `

After you clone the project, or download the source code the root directory has one main CMakeLists.txt. The CMake files use Fetch_Content to automatically download and set up SFML and other dependencies in the `shared` directory. 

All you need to do is create a build folder, and run cmake passing the build folder as the output build directory.

## Linux / MacOS 
`git clone https://github.com/blrbrb/Pegasus`
`cd Pegasus && mkdir build`
`cmake -B build && cmake --build build`



## Windows 
