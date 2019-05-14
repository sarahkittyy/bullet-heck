cmake_minimum_required(VERSION 3.13)
project(BulletHeck)

option(BUILD_DEBUG "Build the debug binaries" off)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall)
if(BUILD_DEBUG)
	add_compile_options(-g)
endif()

find_package(SFML 2.5 REQUIRED COMPONENTS graphics window audio network system)

file(GLOB_RECURSE sources "src/*.cpp")

add_executable(bulletheck ${sources})

target_link_libraries(bulletheck sfml-graphics sfml-window sfml-audio sfml-network sfml-system stdc++fs lua)
target_include_directories(bulletheck PUBLIC "include" "lib")
