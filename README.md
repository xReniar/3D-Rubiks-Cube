# 3D Rubik's Cube 

3D Rubik's cube implementation using C/C++ with Vulkan. This project was made with the following software version:
- Linux Ubuntu 22.04
- Vulkan Instance Version: `1.3.204`
- C/C++ compiler Version: `11.4.0`
- Python version: `3.10.12`
## How to use
- Is it possible to watch the cube with different angles just use `WASD` to move and arrow keys to move the view. Use `Q` to go down and `E` to go up.
- The possible moves are `UDFRBL`, the keys associated with these turns are respectively from `1` to `6`. To enable/disable double turns press `9` and to enable/disable anticlockwise turns just press `0`.
- The projects uses the `Kociemba algorithm`, to solve the cube just press `space`. The first time solving the cube will be slow because the solver has to generate the prunetables for calculating the solution, after that the time for calculating the solution should be around 2-3 seconds. When calculating the solution the cube turns are disabled

If everything works this should be the output:

https://github.com/user-attachments/assets/e3b77d16-a1e4-4d06-a2bd-28c04624950b
## Requirements
The following instructions are for `Ubuntu`, for other operating systems read [here](https://vulkan-tutorial.com/Development_environment).
### Check if g++ and python3 are installed
Ubuntu comes with python preinstalled but to make sure that everything is installed just run this commands:
```bash
g++ --version
python3 --version
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
### Packages for cube solver
The cube is solved using `Kociemba` algorithm, for ubuntu you might need to install libffi system library, for more information check [here](https://github.com/muodov/kociemba).
Also the solver is written with python so `python-dev` is necessary to make c/c++ and python communicate:
```bash
# libffi system library
sudo apt-get install libffi-dev

# python dev
sudo apt-get install python3-dev
```
## Compile & Execute
To compile and execute just run `run.sh`:
```bash
bash run.sh
```