cmake_minimum_required(VERSION 3.0)
project(steg_main)

find_package(OpenCV REQUIRED)

add_executable(steg_main main.cpp utils.cpp LSB.cpp PM1.cpp QIM.cpp)
target_link_libraries(steg_main ${OpenCV_LIBS})

# tests
include_directories(doctest)

add_executable(MyTests test.cpp utils.cpp LSB.cpp PM1.cpp QIM.cpp)
target_link_libraries(MyTests ${OpenCV_LIBS})

target_include_directories(MyTests PRIVATE doctest)

enable_testing()

add_test(NAME MyTests COMMAND MyTests)
