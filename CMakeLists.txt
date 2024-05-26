cmake_minimum_required(VERSION 3.0)
project(steg_main)

find_package(OpenCV REQUIRED)

add_executable(steg_main main.cpp utils.cpp LSB.cpp PM1.cpp QIM.cpp)
target_link_libraries(steg_main ${OpenCV_LIBS})