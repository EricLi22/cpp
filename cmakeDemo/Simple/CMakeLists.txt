# '#'行后面的都是注释

# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (Calc)

# 设置版本号
set (Demo_VERSION_MAJOR 1)
set (Demo_VERSION_MINOR 0)

# 加入一个配置头文件，用于处理 CMake 对源码的设置
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )

# 是否使用自己的 MathFunctions 库
option (USE_MYMATH
       "Use provided math implementation" OFF)

# 是否加入 MathFunctions 库
if (USE_MYMATH)
 include_directories ("${PROJECT_SOURCE_DIR}/math")
 add_subdirectory (math)
 set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif (USE_MYMATH)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 指定生成目标
add_executable(main main.cpp)

# 添加链接库
target_link_libraries(main ${EXTRA_LIBS})

# 指定安装路径
install (TARGETS main DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/config.h"
         DESTINATION include)

enable_testing()
# 测试程序是否成功运行
add_test (test_run main)


# 构建一个 CPack 安装包
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE
  "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set (CPACK_PACKAGE_VERSION_MAJOR "${Demo_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${Demo_VERSION_MINOR}")
include (CPack)
