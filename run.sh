#!bin/bash
g++ -std=c++17 -O2 \
    main.cpp \
    -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi \
    src/cube/Side.cpp \
    src/cube/Cube.cpp \
    src/solver/Solver.cpp \
    -o main ; ./main