CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

VulkanProject: $(shell find . -name "*.cpp")
	g++ $(CFLAGS) -o VulkanProject $^ $(LDFLAGS)

PHONY: test clean

test: VulkanProject
	./VulkanProject

clean:
	rm -f VulkanProject