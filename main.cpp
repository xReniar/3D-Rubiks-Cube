#include"src/Rubiks.hpp"

int main(){
    Cube cube;
    Solver solver;

    CubeGUI rubikscube;

    try {
        rubikscube.run();
    } catch (const std::exception& e) {
        return EXIT_FAILURE;
    }

    /*
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);

    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    glm::mat4 matrix;
    glm::vec4 vec;
    auto test = matrix * vec;

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    */

    //solver.solve(cube);

    //cube.turn("UDFRBL");
    return 0;
}