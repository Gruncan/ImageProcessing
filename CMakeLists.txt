cmake_minimum_required(VERSION 3.10)

project(ImageProcessing VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)


add_subdirectory(Netpbm)

add_executable(ImageProcessing main.cpp)

target_link_libraries(ImageProcessing PRIVATE ${CMAKE_BINARY_DIR}/Netpbm/libnetpbm.a)