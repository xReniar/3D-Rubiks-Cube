#!bin/bash

# declaring path variables
GLSLC_PATH="/usr/local/bin"
TINYOBJLOADER_PATH="./include"
PYTHON_PATH="/usr/include/python3.10"

# compling shaders using glslc
${GLSLC_PATH}/glslc shaders/shader.vert -o shaders/shader.vert.spv
${GLSLC_PATH}/glslc shaders/shader.frag -o shaders/shader.frag.spv

# compile project
g++ -std=c++17 -O2 \
    -I${TINYOBJLOADER_PATH} \
    -I${PYTHON_PATH} \
    main.cpp \
    src/cube/*.cpp \
    src/solver/Solver.cpp \
    src/gui/*.cpp \
    -o VulkanProject -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi -lpython3.10

# execute project
./VulkanProject