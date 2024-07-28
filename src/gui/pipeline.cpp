#include"pipeline.hpp"

#include<iostream>
#include<fstream>
#include<stdexcept>


Pipeline::Pipeline(
        Device& device,
        const std::string& vertFilePath,
        const std::string& fragFilePath,
        const PipelineConfigInfo& configInfo
    ) : device{device} {
    createGraphicsPipeline(vertFilePath, fragFilePath, configInfo);
}

PipelineConfigInfo Pipeline::defaultPipelineConfigInfo(uint32_t width, uint32_t height){
    PipelineConfigInfo configInfo{};
    
    return configInfo;
}

std::vector<char> Pipeline::readFile(const std::string& filePath){
    std::ifstream file{filePath, std::ios::ate | std::ios::binary };

    if(!file.is_open())
        throw std::runtime_error("failed to open file: " + filePath);

    size_t fileSize = static_cast<size_t>(file.tellg());
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();
    return buffer;
}

void Pipeline::createGraphicsPipeline(const std::string& vertFilePath, const std::string& fragFilePath, const PipelineConfigInfo& configInfo){
    auto vertCode = readFile(vertFilePath);
    auto fragCode = readFile(fragFilePath);
}

void Pipeline::createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule){
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    if(vkCreateShaderModule(device.device(), &createInfo, nullptr, shaderModule) != VK_SUCCESS)
        throw std::runtime_error("failed to create shader module");
}