#!bin/bash
g++ -std=c++17 -O2 \
    main.cpp \
    src/cube/Side.cpp \
    src/cube/Cube.cpp \
    src/solver/Solver.cpp \
    src/gui/CubeGUI.cpp \
    -o main -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi ; ./main