cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include("tools/gate/cmake/HunterGate.cmake")

HunterGate(
        URL "https://github.com/ruslo/hunter/archive/v0.23.31.tar.gz"
        SHA1 "3d94b8522541c4c8eaac606f4c47d09322a8019c"
)

project(evolution)
string(APPEND CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-unused-command-line-argument -Wnon-virtual-dtor -pedantic")

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

hunter_add_package(nlohmann_json)
find_package(nlohmann_json CONFIG REQUIRED)

hunter_add_package(Boost COMPONENTS system filesystem)
find_package(Boost CONFIG REQUIRED system filesystem)


set(EXECUTABLE_NAME "Evolution")

add_executable(evolution_tests
        project/main.cpp
        project/sourses/Map.cpp
        project/sourses/Evolution.cpp
        project/sourses/Keyboard.cpp
        project/sourses/Hexagon.cpp
        project/sourses/Pixel.cpp
        project/sourses/Link.cpp
        project/sourses/Brain.cpp
        project/sourses/Neuron.cpp
        project/sourses/TrainAlgorithm.cpp
        project/sourses/Button.cpp
        project/tests/Keyboard_test.cpp
        project/tests/Brain_tests.cpp)

add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)

set(SFML_DIR "${CMAKE_CURRENT_LIST_DIR}/tools/sfml")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/tools/sfml/cmake/Modules")
find_package(SFML REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})
message(${SFML_LIBRARIES})

target_include_directories(evolution_tests PUBLIC project/include)
target_link_libraries(evolution_tests
        GTest::main
        nlohmann_json::nlohmann_json
        Boost::system
        Boost::filesystem
        ${SFML_LIBRARIES})

enable_testing()
add_test(NAME tests COMMAND evolution_tests)