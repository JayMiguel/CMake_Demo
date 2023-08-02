# 最低版本要求
cmake_minimum_required(VERSION 3.0)

# 项目信息
project(Demo2)

# 查找当前目录下的所有源文件，并将名称保存到DIR_SRCS中
aux_source_directory(. DIR_SRCS)

# 添加子目录
add_subdirectory(math)

# 指定生成可执行文件
add_executable(Demo2 main.cpp)

# 目标与库文件链接
target_link_libraries(Demo2 MathFunctions)
