#!bin/bash

# declaring path variables
BIN_PATH="/usr/local/bin"

# compling shaders using glslc
${BIN_PATH}/glslc shaders/shader.vert -o shaders/shader.vert.spv
${BIN_PATH}/glslc shaders/shader.frag -o shaders/shader.frag.spv

# compile project
g++ -std=c++17 -O2 \
    main.cpp \
    src/cube/*.cpp \
    src/solver/Solver.cpp \
    src/gui/*.cpp \
    -o main -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

# execute project
./main