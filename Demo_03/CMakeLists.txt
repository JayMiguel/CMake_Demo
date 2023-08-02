# 最低版本要求
cmake_minimum_required(VERSION 3.0)

# 项目信息
project(Demo3)

# 加入一个配置头文件，用于处理CMake对源码的设置
configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
)

# 提供一个选项，用于选择是否使用自己的MathFunctions库
option(USE_MYMATH "Use provided math implementation" ON)

# 如果选项开启，则进行以下的配置
if (USE_MYMATH)
    include_directories("${PROJECT_SOURCE_DIR}/math")
    add_subdirectory(math)
    # 保留原来的附加库列表，并向其中添加MathFunctions库
    set(EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif(USE_MYMATH)

# 查找当前目录下的所有源文件，并将名称保存到DIR_SRCS中
aux_source_directory(. DIR_SRCS)
 
# 指定生成目标
add_executable(Demo3 main.cpp)

# 目标与依赖库链接
target_link_libraries(Demo3 ${EXTRA_LIBS})
