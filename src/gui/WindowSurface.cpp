#include"CubeGUI.hpp"

void CubeGUI::setupDebugMessenger(){
    if (!enableValidationLayers) return;
    VkDebugUtilsMessengerCreateInfoEXT createInfo;
    this->populateDebugMessengerCreateInfo(createInfo);
    if (CreateDebugUtilsMessengerEXT(this->instance, &createInfo, nullptr, &(this->debugMessenger)) != VK_SUCCESS)
        throw std::runtime_error("failed to set up debug messenger!");
}

void CubeGUI::createSurface() {
    if (glfwCreateWindowSurface(this->instance, this->window, nullptr, &(this->surface)) != VK_SUCCESS)
        throw std::runtime_error("failed to create window surface!");
}