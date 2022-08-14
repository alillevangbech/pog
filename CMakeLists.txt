cmake_minimum_required(VERSION 3.17)

project(pog LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory("./lib")

find_package(OpenGL REQUIRED)

add_executable(pog
			   main.cpp
			   pog.cpp)

target_link_libraries(
	pog
	PUBLIC imgui OpenGL::GL
)
