cmake_minimum_required(VERSION 3.0)
project(steg_main)

find_package(OpenCV REQUIRED)

add_executable(steg_main main.cpp utils.cpp LSB.cpp PM1.cpp QIM.cpp)
target_link_libraries(steg_main ${OpenCV_LIBS})

# Подключите библиотеку doctest (здесь предполагается, что doctest.h находится в директории "external/doctest")
include_directories(doctest)

# Добавьте тестовый исполняемый файл
add_executable(MyTests test.cpp utils.cpp LSB.cpp PM1.cpp QIM.cpp)
target_link_libraries(MyTests ${OpenCV_LIBS})

# Ссылка на библиотеку doctest
target_include_directories(MyTests PRIVATE doctest)

# Включить поддержку тестирования и CTest
enable_testing()

# Зарегистрировать MyTests в CTest
add_test(NAME MyTests COMMAND MyTests)
