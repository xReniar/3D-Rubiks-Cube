cmake_minimum_required(VERSION 3.21)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(WIN32)
  set(CMAKE_TOOLCHAIN_FILE "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/vcpkg/scripts/buildsystems/vcpkg.cmake")
  set(VK_ADD_LAYER_PATH "${CMAKE_BINARY_DIR}/vcpkg_installed/x64-windows/bin")
endif()
if (LINUX)
  set(VCPKG_SHARE "./vcpkg_installed/x64-linux/share/")
  set(CMAKE_TOOLCHAIN_FILE "~/Workspaces/Tools/vcpkg/scripts/buildsystems/vcpkg.cmake")
  set(unofficial-shaderc_DIR "${VCPKG_SHARE}/unofficial-shaderc/")
  set(glslang_DIR "${VCPKG_SHARE}/glslang/")
  set(SPIRV-Tools_DIR "${VCPKG_SHARE}/spirv-tools/")
  set(SPIRV-Tools-opt_DIR "${VCPKG_SHARE}/spirv-tools-opt/")
  set(VK_ADD_LAYER_PATH "${VCPKG_SHARE}/vulkan/explicit_layer.d/")
endif()

# For clang-tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(INCLUDE_INSTALL_DIR include)
set(KOCIEMBA_SRC ${CMAKE_SOURCE_DIR}/src/solver/ckociemba)
# Add the include directories
include_directories(${KOCIEMBA_SRC}/include)


# Set the project name and version
project(RubiksCube VERSION 1.0)

find_package(glfw3 CONFIG REQUIRED)
find_package(Vulkan REQUIRED)

find_package(unofficial-shaderc CONFIG REQUIRED)

find_program(glslc_executable NAMES glslc HINTS unofficial-shaderc::glslc ${CMAKE_SOURCE_DIR}/vcpkg_installed/x64-linux/tools/shaderc)

# ${GLSLC_PATH}/glslc shaders/shader.frag -o shaders/shader.frag.spv
function(compile_shader target)
  cmake_parse_arguments(PARSE_ARGV 1 arg "" "ENV;FORMAT" "SOURCES")

  foreach(source ${arg_SOURCES})
    add_custom_command(
      OUTPUT ${CMAKE_BINARY_DIR}/${source}.${arg_FORMAT}
      DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${source}

      # DEPFILE ${CMAKE_BINARY_DIR}/${source}.d
      # COMMAND
      # ${glslc_executable}
      # $<$<BOOL:${arg_ENV}>:--target-env=${arg_ENV}>
      # $<$<BOOL:${arg_FORMAT}>:-mfmt=num>
      # -MD -MF ${CMAKE_BINARY_DIR}/${source}.d
      # -o ${CMAKE_BINARY_DIR}/${source}.${arg_FORMAT}
      # ${CMAKE_CURRENT_SOURCE_DIR}/${source}

      COMMAND
      ${glslc_executable}
      ${CMAKE_CURRENT_SOURCE_DIR}/${source}
      -o ${CMAKE_BINARY_DIR}/${source}.${arg_FORMAT}

      COMMENT "Compiling ${source} to ${source}.${arg_FORMAT}"
    )
    target_sources(${target} PRIVATE ${CMAKE_BINARY_DIR}/${source}.${arg_FORMAT})
  endforeach()
endfunction()

# Add your project files
file(GLOB_RECURSE ALL_CPP_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE C_SOURCES "${CMAKE_SOURCE_DIR}/src/solver/ckociemba/*.c")

# Create a library from the C source files
add_library(cKociemba STATIC ${C_SOURCES})

# Add the executable
add_executable(${PROJECT_NAME} main.cpp ${ALL_CPP_FILES})

compile_shader(${PROJECT_NAME}
  ENV vulkan
  FORMAT spv
  SOURCES
  shaders/shader.vert
  shaders/shader.frag
)

# Define GLM_ENABLE_EXPERIMENTAL
target_compile_definitions(${PROJECT_NAME} PRIVATE GLM_ENABLE_EXPERIMENTAL)

# Include directories for the executable
target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_SOURCE_DIR}/include
  ${KOCIEMBA_SRC}/include
  ${CMAKE_SOURCE_DIR}/src
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
  glfw
  Vulkan::Vulkan
  cKociemba
)

# Add custom target for the models folder
add_custom_target(copy_models ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/models ${CMAKE_BINARY_DIR}/models
  DEPENDS ${CMAKE_SOURCE_DIR}/models
)

# Add dependency to the main target
add_dependencies(${PROJECT_NAME} copy_models)
