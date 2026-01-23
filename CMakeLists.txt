cmake_minimum_required(VERSION 3.10)
project(ShoppingAppFinal)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp" "main.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

add_executable(ShoppingAppFinal ${SOURCES} ${HEADERS})
