cmake_minimum_required(VERSION 3.20)

project(SFMLTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin")

set(SFML_DIR "${CMAKE_CURRENT_LIST_DIR}/lib/cmake/SFML")

find_package(SFML 3 CONFIG REQUIRED COMPONENTS graphics window system)

add_executable(SFMLTest ../C++/SFML/SFMLTest/SFMLTest.cpp)

target_include_directories(SFMLTest PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/include"
)

target_link_libraries(SFMLTest PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)
