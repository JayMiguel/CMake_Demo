# 在当前目录下查找所有源文件，并把名称保存在DIR_LIB_SRCS
aux_source_directory(. DIR_LIB_SRCS)

# 指定生成库文件
add_library(MathFunctions ${DIR_LIB_SRCS})