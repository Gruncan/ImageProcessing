cmake_minimum_required(VERSION 3.23)
project(ImageProcessing)

set(CMAKE_CXX_STANDARD 17)

add_library(ImageProcessing library.cpp Netpbm/Netpbm.h Netpbm/PGM.h)

add_executable(ImageProcessingRun main.cpp Netpbm/PPM.h Netpbm/PBM.h)
