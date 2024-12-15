cmake_minimum_required(VERSION 3.10)
project(lab4)

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
add_executable(lab4_main main.cpp)

add_library(lab4_lib_utils src/utils.cpp)

target_link_libraries(lab4_main PRIVATE lab4_lib_utils)

# Добавление тестов
enable_testing()

add_executable(lab4_tests test/test.cpp)
target_link_libraries(lab4_tests lab4_lib_utils)
target_link_libraries(lab4_tests gtest_main)

# Добавление тестов в тестовый набор
add_test(NAME lab4_tests COMMAND lab4_tests)