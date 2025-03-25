cmake_minimum_required(VERSION 3.10)
project(WinRandom)

set(CMAKE_CXX_STANDARD 11)

# 设置可执行文件输出目录为当前工作区的bin文件夹
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# 确保bin目录存在
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_executable(WinRandom main.cpp WinRandom.cpp)
target_link_libraries(WinRandom bcrypt)