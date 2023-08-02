# 最低版本要求
cmake_minimum_required(VERSION 3.0)

# 项目信息
project(Demo5)

# 加入一个配置头文件，用于处理CMake对源码的设置
configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
)

# 在其他目录构建时，源码中会找不到构建生成的头文件
# 所以必须把构建目录加入包含目录列表
include_directories("${PROJECT_BINARY_DIR}")

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
add_executable(Demo5 main.cc)

# 目标与依赖库链接
target_link_libraries(Demo5 ${EXTRA_LIBS})

# 指定安装目录
install(TARGETS Demo5 DESTINATION "${PROJECT_BINARY_DIR}/bin")
install(FILES "${PROJECT_BINARY_DIR}/config.h" DESTINATION "${PROJECT_BINARY_DIR}/include")

# 启用测试
enable_testing()

# 添加一个测试
add_test(test_run Demo5 5 2)

# 添加一个测试，并对测试结果进行校验
add_test(test_usage Demo5)
set_tests_properties(test_usage PROPERTIES PASS_REGULAR_EXPRESSION "Usage: .* base exponent")

add_test(test_5_2 Demo5 5 2)
set_tests_properties(test_5_2 PROPERTIES PASS_REGULAR_EXPRESSION "is 25")

add_test(test_10_5 Demo5 10 5)
set_tests_properties(test_10_5 PROPERTIES PASS_REGULAR_EXPRESSION "is 100000")

add_test(test_2_10 Demo5 2 10)
set_tests_properties(test_2_10 PROPERTIES PASS_REGULAR_EXPRESSION "is 1024")

# 定义一个宏，用来简化添加测试用例的操作
macro (do_test arg1 arg2 result)
    add_test(test_${arg1}_${arg2} Demo5 ${arg1} ${arg2})
    set_tests_properties(test_${arg1}_${arg2} PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro(do_test)

# 使用宏来添加测试用例
do_test(5 2 "is 25")
do_test(10_5 "is 100000")
do_test(2 10 "is 1024")