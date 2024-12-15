cmake_minimum_required(VERSION 3.10)
project(lab3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавление опций компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

# Установка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  TLS_VERIFY false
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# компиляция файлов проекта
add_executable(lab3_main main.cpp)

add_library(lab3_lib_utils src/utils.cpp)
add_library(lab3_lib_point src/point.cpp)
add_library(lab3_lib_figure src/figure.cpp)
add_library(lab3_lib_triangle src/triangle.cpp)
add_library(lab3_lib_hexagon src/hexagon.cpp)
add_library(lab3_lib_octagon src/octagon.cpp)

target_link_libraries(lab3_lib_point PRIVATE lab3_lib_utils)
target_link_libraries(lab3_lib_triangle PRIVATE lab3_lib_utils)
target_link_libraries(lab3_lib_hexagon PRIVATE lab3_lib_utils)
target_link_libraries(lab3_lib_octagon PRIVATE lab3_lib_utils)

target_link_libraries(lab3_lib_triangle PRIVATE lab3_lib_point)
target_link_libraries(lab3_lib_hexagon PRIVATE lab3_lib_point)
target_link_libraries(lab3_lib_octagon PRIVATE lab3_lib_point)

target_link_libraries(lab3_main PRIVATE lab3_lib_utils)
target_link_libraries(lab3_main PRIVATE lab3_lib_point)
target_link_libraries(lab3_main PRIVATE lab3_lib_figure)
target_link_libraries(lab3_main PRIVATE lab3_lib_triangle)
target_link_libraries(lab3_main PRIVATE lab3_lib_hexagon)
target_link_libraries(lab3_main PRIVATE lab3_lib_octagon)

# Добавление тестов
enable_testing()

add_executable(tests_lab3 test/test.cpp)
target_link_libraries(tests_lab3 lab3_lib_utils)
target_link_libraries(tests_lab3 lab3_lib_point)
target_link_libraries(tests_lab3 lab3_lib_figure)
target_link_libraries(tests_lab3 lab3_lib_triangle)
target_link_libraries(tests_lab3 lab3_lib_hexagon)
target_link_libraries(tests_lab3 lab3_lib_octagon)
target_link_libraries(tests_lab3 gtest_main)

# Добавление тестов в тестовый набор
add_test(NAME tests_lab3 COMMAND tests_lab3)