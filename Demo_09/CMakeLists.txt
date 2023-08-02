# 最低版本要求
cmake_minimum_required(VERSION 3.0)

# 项目信息
project(Demo9)

# 版本号
set(Demo_VERSION_MAJOR 1)
set(Demo_VERSION_MINOR 0)

set(CMAKE_BUILD_TYPE Debug)

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
add_executable(Demo9 main.cc)

# 目标与依赖库链接
target_link_libraries(Demo9 ${EXTRA_LIBS})

# 安装目录
set(CMAKE_INSTALL_PREFIX "${PROJECT_BINARY_DIR}/install")

# 指定安装目录
install(TARGETS Demo9 DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/config.h" DESTINATION include)

# 打包配置
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${Demo_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Demo_VERSION_MINOR}")
include(CPack)