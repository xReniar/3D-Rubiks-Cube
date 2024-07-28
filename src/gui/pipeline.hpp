#ifndef PIPELINE_H
#define PIPELINE_H

#include"device.hpp"

#include<string>
#include<vector>

struct PipelineConfigInfo{};

class Pipeline {
public:
    Pipeline(
        Device& device,
        const std::string& vertFilePath,
        const std::string& fragFilePath,
        const PipelineConfigInfo& configInfo
    );
    ~Pipeline() {}

    Pipeline(const Pipeline&) = delete;
    void operator = (const Pipeline&) = delete;

    static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);

private:
    Device& device;
    VkPipeline graphicsPipeline;
    VkShaderModule vertShaderModule;
    VkShaderModule fragShaderModule;

    static std::vector<char> readFile(const std::string& filePath);
    void createGraphicsPipeline(
        const std::string& vertFilePath,
        const std::string& fragFilePath,
        const PipelineConfigInfo& configInfo
    );
    void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);
};

#endif