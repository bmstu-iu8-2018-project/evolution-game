cmake_minimum_required(VERSION 3.9.2)

include("vendor/gate/cmake/HunterGate.cmake")

HunterGate(
        URL "https://github.com/ruslo/hunter/archive/v0.23.31.tar.gz"
        SHA1 "3d94b8522541c4c8eaac606f4c47d09322a8019c"
)

project(evolution)
string(APPEND CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-unused-command-line-argument -Wnon-virtual-dtor -pedantic")

hunter_add_package(nlohmann_json)
find_package(nlohmann_json CONFIG REQUIRED)

hunter_add_package(Boost COMPONENTS system filesystem)
find_package(Boost CONFIG REQUIRED system filesystem)

project(Evolution)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SFML_LIBS ${CMAKE_SOURCE_DIR}/build/sfml/lib/*)
file(GLOB GTEST_LIBS ${CMAKE_SOURCE_DIR}/build/gtest/libgtest*)

# CLASSES
file(GLOB_RECURSE CLASSES_SOURCES project/sourses/*.cpp)
add_library(classes ${CLASSES_SOURCES})
target_link_libraries(classes ${SFML_LIBS}
        nlohmann_json::nlohmann_json
        Boost::system
        Boost::filesystem)
target_include_directories(classes PUBLIC project)
target_include_directories(classes PUBLIC tools/sfml/include)

# GAME
set(SOURCES project/main.cpp)
add_executable(game ${SOURCES})
target_link_libraries(game classes
        nlohmann_json::nlohmann_json
        Boost::system
        Boost::filesystem)
target_include_directories(game PUBLIC src)
target_include_directories(game PUBLIC ${CMAKE_SOURCE_DIR}/tools/sfml/include)

# TESTS
file(GLOB_RECURSE TEST_SOURCES project/tests/*.cpp)
add_executable(tests ${TEST_SOURCES})

target_link_libraries(tests ${GTEST_LIBS})
target_link_libraries(tests classes
        nlohmann_json::nlohmann_json
        Boost::system
        Boost::filesystem)
target_include_directories(tests PUBLIC tools/sfml/include tools/gtest/include)
target_include_directories(tests PUBLIC ${CMAKE_SOURCE_DIR}/project)

add_custom_target(NAME run_tests COMMAND tests)
