cmake_minimum_required(VERSION 3.10)

# 项目名称
project(AFilter LANGUAGES C)

# 设置 C 标准
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# 添加源文件
set(SRC_FILES
    src/afilter_mid.c
    src/afilter.c
)

# 添加头文件路径
include_directories(src)

# 检查并下载 Unity 测试框架
include(FetchContent)
FetchContent_Declare(
    Unity
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG        master # 或指定版本号，例如 v2.5.2
)
FetchContent_MakeAvailable(Unity)

# 添加 Unity 的源文件
set(UNITY_SRC
    ${unity_SOURCE_DIR}/src/unity.c
)

# 添加测试文件
set(TEST_FILES
    test/unity_test.c
)

# 添加 Unity 的头文件路径
include_directories(${unity_SOURCE_DIR}/src)

# 生成可执行文件
add_executable(AFilterTest ${SRC_FILES} ${TEST_FILES} ${UNITY_SRC})