#ifndef PIPELINE_H
#define PIPELINE_H

#include"device.hpp"
#include"model.hpp"

#include<string>
#include<vector>
#include "pipeline_config_info.hpp"

class Pipeline {
public:
    Pipeline(
        Device& device,
        const std::string& vertFilePath,
        const std::string& fragFilePath,
        const PipelineConfigInfo& configInfo
    );
    ~Pipeline();

    Pipeline(const Pipeline&) = delete;
    Pipeline& operator = (const Pipeline&) = delete;

    void bind(VkCommandBuffer commandBuffer);
    // static void defaultPipelineConfigInfo(PipelineConfigInfo& configInfo);

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