cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include("/home/anastasia/CLionProjects/evolution/tools/gate/gate-42c1c27cdd556dcbc358c6ba8ad7a72a68ee2a62/cmake/HunterGate.cmake")

huntergate(
        URL "https://github.com/ruslo/hunter/archive/v0.23.31.tar.gz"
        SHA1 "3d94b8522541c4c8eaac606f4c47d09322a8019c"
)
project(Evolution)

string(APPEND CMAKE_CXX_FLAGS " -pedantic -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")

set(EXECUTABLE_NAME "Evolution")

hunter_add_package(GTest)
hunter_add_package(Boost COMPONENTS system filesystem)
find_package(Boost CONFIG REQUIRED system filesystem)
find_package(GTest CONFIG REQUIRED)

add_executable(${EXECUTABLE_NAME} main.cpp Map.hpp Map.cpp  Evolution.hpp Evolution.cpp Keyboard.hpp Keyboard.cpp Hexagon.hpp
        Hexagon.cpp Food.hpp Pixel.cpp Pixel.hpp NetworkFunction.hpp Link.cpp Link.hpp Brain.cpp Brain.hpp
        Neuron.cpp Neuron.hpp NeuronCreator.hpp TrainAlgorithm.cpp TrainAlgorithm.hpp Button.cpp Button.hpp)


target_include_directories(${EXECUTABLE_NAME}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        )
target_link_libraries(${EXECUTABLE_NAME} GTest::main
        Boost::system
        Boost::filesystem)
target_link_libraries(${EXECUTABLE_NAME}
        Boost::filesystem
        Boost::system)
add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)
enable_testing()
add_test(NAME unit_tests COMMAND ${EXECUTABLE_NAME})

set(SFML_DIR "/home/anastasia/SFML-2.3.2/share/SFML")
set(CMAKE_MODULE_PATH "/home/anastasia/SFML-2.3.2/share/SFML/cmake/Modules" ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})