# 3D Rubik's Cube 
3D Rubik's cube implementation using C/C++ with Vulkan.

This project was made with the following software version:
- Linux Ubuntu 22.04
- Vulkan Instance Version: `1.3.204`
- C/C++ compiler Version: `11.4.0`
## How to use
To possible moves are `UDFRBL`, the keys associated with these turns are respectively from `1` to `6`. To enable/disable double turns press `9` and to enable/disable anticlockwise turns just press `0`
## Requirements
### Install Vulkan
To install `Vulkan` and development tools just execute in the terminal:
```bash
sudo apt-get install vulkan-tools
sudo apt-get install libvulkan-dev
sudo apt-get install vulkan-validationlayers-dev
sudo apt-get install spirv-tools
sudo apt-get install libglfw3-dev
sudo apt-get install libglm-dev
sudo apt-get install libxi-dev
sudo apt-get install libxxf86vm-dev
```
### Install glslc
The steps to install `glslc` may vary depending which OS you are using, just follow these [instructions](https://vulkan-tutorial.com/Development_environment#page_Shader-Compiler) and place it in `usr/local/bin`.
## Compile & Execute
To compile and execute just run `run.sh`:
```bash
bash run.sh
```