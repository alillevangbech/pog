cmake_minimum_required(VERSION 3.17)

project(pog LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory("./lib")

find_package(OpenGL REQUIRED)

add_executable(pog
			   main.cpp
			   pog.cpp
			   glfw_utils.cpp)

target_link_libraries(
	pog
	PUBLIC imgui OpenGL::GL
)

add_custom_command(TARGET pog POST_BUILD        # Adds a post-build event to MyTest
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/shortcut.pog"      # <--this is in-file
        $<TARGET_FILE_DIR:pog>)    


install(TARGETS pog DESTINATION .)
install(FILES ./shortcut.pog DESTINATION .)
