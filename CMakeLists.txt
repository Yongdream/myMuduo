cmake_minimum_required(VERSION 2.5)
project(mymuduo)

# 编译成动态库
# 设置动态库路径
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
# 设置调试选项 启动c++11语言标准
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")

# 参与编译的源代码文件
aux_source_directory(. SRC_LIST)

# 编译生成动态库mymuduo
add_library(mymuduo SHARED ${SRC_LIST})

