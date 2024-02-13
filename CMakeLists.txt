cmake_minimum_required(VERSION 3.26.0)

project(OpenGL)

add_executable(OpenGL 
	src/Render.cpp
	src/glad.c
	src/src.h
	src/Shader.cpp
	src/Rectangle.cpp
		src/Algebra.h)

target_link_directories(OpenGL 
	PRIVATE ${CMAKE_SOURCE_DIR}/libs)


target_link_libraries(OpenGL 
	glfw3 
	OpenGL32)

target_include_directories(OpenGL 
	PUBLIC ${CMAKE_SOURCE_DIR}/include)
