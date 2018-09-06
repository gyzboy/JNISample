# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

#如果您在 CMake 构建脚本中重命名或移除某个库，您需要先清理项目，
#Gradle 随后才会应用更改或者从 APK 中移除旧版本的库。要清理项目，请从菜单栏中选择 Build > Clean Project

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

#NDK 还以源代码的形式包含一些库，您在构建和关联到您的原生库时需要使用这些代码。您可以使用 CMake 构建脚本中的 add_library() 命令，
#将源代码编译到原生库中。要提供本地 NDK 库的路径，您可以使用 ANDROID_NDK 路径变量，Android Studio 会自动为您定义此变量
add_library( app-glue
             STATIC
             ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c )

#添加预构建库与为 CMake 指定要构建的另一个原生库类似。不过，由于库已经预先构建，您需要使用 IMPORTED 标志告知 CMake 您只希望将库导入到项目中
add_library( imported-lib
              SHARED
              IMPORTED )
#使用 set_target_properties() 命令指定库的路径
set_target_properties( # Specifies the target library.
                       imported-lib

                       # Specifies the parameter you want to define.
                       PROPERTIES IMPORTED_LOCATION

                       # Provides the path to the library you want to import.
                       imported-lib/src/${ANDROID_ABI}/libimported-lib.so )
include_directories( imported-lib/include/ )

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