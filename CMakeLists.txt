cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(Digital_recognition)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 包含头文件目录
include_directories(include)

# 查找源文件
file(GLOB_RECURSE SOURCES "srcs/*.cpp" "demo/*.cpp")

# 添加可执行文件
add_executable(Digital_recognition ${SOURCES})