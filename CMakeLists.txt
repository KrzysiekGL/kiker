cmake_minimum_required(VERSION 3.10)

project(kiker VERSION 0.3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

add_subdirectory(lib/cgl)

add_executable(kiker src/main.cpp)
target_link_libraries(kiker PUBLIC cgl)

target_compile_options(kiker
	PRIVATE
	-Wall
	-Werror
	-O3
	)


target_include_directories(kiker
	PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/src"
	INTERFACE
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
)

