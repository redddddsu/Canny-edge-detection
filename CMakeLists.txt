cmake_minimum_required(VERSION 3.10)
project(CannyEdgeDetection)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(ced src/main.cpp src/gaussian.cpp src/nonMaxSup.cpp src/sobel.cpp src/threshhold.cpp)
