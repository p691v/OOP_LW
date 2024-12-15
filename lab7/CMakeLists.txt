cmake_minimum_required(VERSION 3.10)
project(lab7)

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

# # компиляция файлов проекта
add_library(lab7_lib_utils src/utils.cpp)
add_library(lab7_lib_Printer src/Printer.cpp)

add_library(lab7_lib_NPC src/NPC.cpp)
add_library(lab7_lib_Pirate src/NPCs/Bandit.cpp)
add_library(lab7_lib_Privateer src/NPCs/Orc.cpp)
add_library(lab7_lib_Rakyat src/NPCs/Werewolf.cpp)

add_library(lab7_lib_FactoryRandom src/factories/FactoryRandom.cpp)
add_library(lab7_lib_FactoryFile src/factories/FactoryFile.cpp)

add_library(lab7_lib_ObserverStdout src/observers/ObserverStdout.cpp)
add_library(lab7_lib_ObserverMurderStdout src/observers/ObserverMurderStdout.cpp)
add_library(lab7_lib_ObserverFile src/observers/ObserverFile.cpp)

add_library(lab7_lib_FightManager src/FightManager.cpp)
add_library(lab7_lib_MoveManager src/MoveManager.cpp)
add_library(lab7_lib_MapDrawer src/MapDrawer.cpp)

add_library(lab7_lib_Game src/Game.cpp)

add_executable(lab7_main main.cpp)

target_link_libraries(lab7_lib_NPC PRIVATE lab7_lib_utils)

target_link_libraries(lab7_lib_Pirate PRIVATE lab7_lib_utils)
target_link_libraries(lab7_lib_Pirate PRIVATE lab7_lib_NPC)

target_link_libraries(lab7_lib_Privateer PRIVATE lab7_lib_utils)
target_link_libraries(lab7_lib_Privateer PRIVATE lab7_lib_NPC)

target_link_libraries(lab7_lib_Rakyat PRIVATE lab7_lib_utils)
target_link_libraries(lab7_lib_Rakyat PRIVATE lab7_lib_NPC)

target_link_libraries(lab7_lib_FactoryRandom PRIVATE lab7_lib_utils)
target_link_libraries(lab7_lib_FactoryRandom PRIVATE lab7_lib_NPC)
target_link_libraries(lab7_lib_FactoryRandom PRIVATE lab7_lib_Pirate)
target_link_libraries(lab7_lib_FactoryRandom PRIVATE lab7_lib_Privateer)
target_link_libraries(lab7_lib_FactoryRandom PRIVATE lab7_lib_Rakyat)

target_link_libraries(lab7_lib_FactoryFile PRIVATE lab7_lib_utils)
target_link_libraries(lab7_lib_FactoryFile PRIVATE lab7_lib_NPC)
target_link_libraries(lab7_lib_FactoryFile PRIVATE lab7_lib_Pirate)
target_link_libraries(lab7_lib_FactoryFile PRIVATE lab7_lib_Privateer)
target_link_libraries(lab7_lib_FactoryFile PRIVATE lab7_lib_Rakyat)

target_link_libraries(lab7_lib_ObserverStdout PRIVATE lab7_lib_utils)
target_link_libraries(lab7_lib_ObserverStdout PRIVATE lab7_lib_NPC)
target_link_libraries(lab7_lib_ObserverStdout PRIVATE lab7_lib_Printer)

target_link_libraries(lab7_lib_ObserverMurderStdout PRIVATE lab7_lib_utils)
target_link_libraries(lab7_lib_ObserverMurderStdout PRIVATE lab7_lib_NPC)
target_link_libraries(lab7_lib_ObserverMurderStdout PRIVATE lab7_lib_Printer)

target_link_libraries(lab7_lib_ObserverFile PRIVATE lab7_lib_utils)
target_link_libraries(lab7_lib_ObserverFile PRIVATE lab7_lib_NPC)

target_link_libraries(lab7_lib_FightManager PRIVATE lab7_lib_utils)
target_link_libraries(lab7_lib_FightManager PRIVATE lab7_lib_NPC)

target_link_libraries(lab7_lib_MoveManager PRIVATE lab7_lib_utils)
target_link_libraries(lab7_lib_MoveManager PRIVATE lab7_lib_NPC)
target_link_libraries(lab7_lib_MoveManager PRIVATE lab7_lib_FightManager)

target_link_libraries(lab7_lib_MapDrawer PRIVATE lab7_lib_utils)
target_link_libraries(lab7_lib_MapDrawer PRIVATE lab7_lib_NPC)
target_link_libraries(lab7_lib_MapDrawer PRIVATE lab7_lib_Printer)

target_link_libraries(lab7_lib_Game PRIVATE lab7_lib_utils)
target_link_libraries(lab7_lib_MapDrawer PRIVATE lab7_lib_Printer)
target_link_libraries(lab7_lib_Game PRIVATE lab7_lib_NPC)
target_link_libraries(lab7_lib_Game PRIVATE lab7_lib_Pirate)
target_link_libraries(lab7_lib_Game PRIVATE lab7_lib_Privateer)
target_link_libraries(lab7_lib_Game PRIVATE lab7_lib_Rakyat)
target_link_libraries(lab7_lib_Game PRIVATE lab7_lib_FactoryRandom)
target_link_libraries(lab7_lib_Game PRIVATE lab7_lib_FactoryFile)
target_link_libraries(lab7_lib_Game PRIVATE lab7_lib_ObserverStdout)
target_link_libraries(lab7_lib_Game PRIVATE lab7_lib_ObserverMurderStdout)
target_link_libraries(lab7_lib_Game PRIVATE lab7_lib_ObserverFile)
target_link_libraries(lab7_lib_Game PRIVATE lab7_lib_FightManager)
target_link_libraries(lab7_lib_Game PRIVATE lab7_lib_MoveManager)
target_link_libraries(lab7_lib_Game PRIVATE lab7_lib_MapDrawer)

target_link_libraries(lab7_main PRIVATE lab7_lib_Game)

# Добавление тестов
enable_testing()

add_executable(lab7_tests test/test.cpp)

target_link_libraries(lab7_tests lab7_lib_utils)
target_link_libraries(lab7_tests lab7_lib_NPC)
target_link_libraries(lab7_tests lab7_lib_Pirate)
target_link_libraries(lab7_tests lab7_lib_Privateer)
target_link_libraries(lab7_tests lab7_lib_Rakyat)
target_link_libraries(lab7_tests lab7_lib_FactoryRandom)
target_link_libraries(lab7_tests lab7_lib_FactoryFile)
target_link_libraries(lab7_tests lab7_lib_utils)
target_link_libraries(lab7_tests gtest_main)

# Добавление тестов в тестовый набор
add_test(NAME lab7_tests COMMAND lab7_tests)