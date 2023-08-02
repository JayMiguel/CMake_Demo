# 最低版本要求
cmake_minimum_required(VERSION 3.0)

# 项目信息
project(Demo8)

# 版本号
set(Demo_VERSION_MAJOR 1)
set(Demo_VERSION_MINOR 0)

# 开启gdb支持
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

# 检查系统是否支持pow函数
include(${CMAKE_ROOT}/Modules/CheckFunctionExists.cmake)
check_function_exists(pow HAVE_POW)

# 加入一个配置头文件，用于处理CMake对源码的设置
configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
)

# 开启后，把当前目录加入包含目录列表
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 如果选项开启，则进行以下的配置
if (NOT HAVE_POW)
    include_directories("${PROJECT_SOURCE_DIR}/math")
    add_subdirectory(math)
    # 保留原来的附加库列表，并向其中添加MathFunctions库
    set(EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif(NOT HAVE_POW)

# 查找当前目录下的所有源文件，并将名称保存到DIR_SRCS中
aux_source_directory(. DIR_SRCS)
 
# 指定生成目标
add_executable(Demo8 main.cc)

# 目标与依赖库链接
target_link_libraries(Demo8 ${EXTRA_LIBS})

# 指定安装目录
install(TARGETS Demo8 DESTINATION "${PROJECT_BINARY_DIR}/bin")
install(FILES "${PROJECT_BINARY_DIR}/config.h" DESTINATION "${PROJECT_BINARY_DIR}/include")

# 启用测试
enable_testing()

# 添加一个测试
add_test(test_run Demo8 5 2)

# 添加一个测试，并对测试结果进行校验
add_test(test_usage Demo8)
set_tests_properties(test_usage PROPERTIES PASS_REGULAR_EXPRESSION "Usage: .* base exponent")

# 定义一个宏，用来简化添加测试用例的操作
macro (do_test arg1 arg2 result)
    add_test(test_${arg1}_${arg2} Demo8 ${arg1} ${arg2})
    set_tests_properties(test_${arg1}_${arg2} PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro(do_test)

# 使用宏来添加测试用例
do_test(5 2 "is 25")
do_test(10 5 "is 100000")
do_test(2 10 "is 1024")