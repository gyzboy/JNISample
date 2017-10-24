# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)#指定cmake版本

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

# 查找cpp目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
#aux_source_directory(src/main/cpp/DIR_LIB_SRCS)

# 导入cpp目录下的所有头文件
#include_directories(src/main/cpp/)

add_library( #生成函数库的名字
             native-lib
             #生成动态函数
             SHARED
             #依赖的cpp文件
             src/main/cpp/native-lib.cpp
             src/main/cpp/testHeader.cpp
             src/main/cpp/testVal.cpp)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( #设置path变量的名称
              log-lib

              #指定要查询库的名字
              #在ndk开发包中查询liblog.so函数库(默认省略lib和.so),路径赋值给log-lib
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( #目标库,和上面生成的函数库名字一至
                       native-lib

                       #连接的库,根据log-lib变量对应liblog.so函数库
                       # included in the NDK.
                       ${log-lib} )