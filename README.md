# 3D Rubik's Cube 
3D Rubik's cube implementation using C/C++ with Vulkan. This project was made with the following software version:
- Linux Ubuntu 22.04
- Vulkan Instance Version: `1.3.204`
- C/C++ compiler Version: `11.4.0`
## How to use
- Is it possible to watch the cube with different angles just use `WASD` to move and arrow keys to move the view. Use `Q` to go down and `E` to go up.
- The possible moves are `UDFRBL`, the keys associated with these turns are respectively from `1` to `6`. To enable/disable double turns press `9` and to enable/disable anticlockwise turns just press `0`.
- The projects uses the `Kociemba algorithm`, to start calculating the solution just press `space`. The first time is always slower because it needs to create a `tables.json` file used to get the solution. For the next solves the average waiting time is usually around 7-10 sec. When pressing space the standard moves are disabled and they'll be enabled when cube is solved.
## Requirements
The following instructions are for `Ubuntu`, for other operating systems read [here](https://vulkan-tutorial.com/Development_environment).
### Install g++ and python
Ubuntu comes with python preinstalled but to make sure that everything is installed just run this commands:
```bash
sudo apt install g++
sudo apt install python3
``` 
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
The shader compiler used is `glslc`, to download it click [here](https://github.com/google/shaderc/blob/main/downloads.md) by selecting the `gcc` release. This will download a `.tgz` file, just extract it and copy the `glslc` executable in `usr/local/bin`:
```bash
# go where the file is downloaded
cd path/to/install.tgz

# extract the file
tar -xzvf install.tgz

# copy to `usr/local/bin`
sudo cp -r install/bin/glslc /usr/local/bin
```
## Compile & Execute
To compile and execute just run `run.sh`:
```bash
bash run.sh
```