# 最低版本要求
cmake_minimum_required(VERSION 3.0)

# 项目信息
project(Demo1)

# 查找当前目录下的所有源文件，并将名称保存到DIR_SRCS中
aux_source_directory(. DIR_SRCS)

# 指定生成目标
add_executable(Demo1 ${DIR_SRCS})
