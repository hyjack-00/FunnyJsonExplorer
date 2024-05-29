cmake_minimum_required(VERSION 3.10)
project(FunnyJsonExplorer)

# for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 包含头文件目录
include_directories(include)

# 将 src 目录下的所有 .cpp 文件添加到变量 SRC_FILES 中
aux_source_directory(src SRC_FILES)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# 添加可执行文件，包含 SRC_FILES 中的所有源文件
add_executable(fje ${SRC_FILES})

