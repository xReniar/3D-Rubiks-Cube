TINYOBJ_PATH = ./include
PYTHON_PATH = /usr/include/python3.10
CFLAGS = -std=c++17 -O2 -I${TINYOBJ_PATH}
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi -lpython3.10
BIN_PATH = /usr/local/bin

VulkanProject: $(shell find . -name "*.cpp")
	${BIN_PATH}/glslc shaders/shader.vert -o shaders/shader.vert.spv
	${BIN_PATH}/glslc shaders/shader.frag -o shaders/shader.frag.spv
	g++ $(CFLAGS) -o VulkanProject $^ $(LDFLAGS)

PHONY: test clean

test: VulkanProject
	./VulkanProject

clean:
	rm -f VulkanProject