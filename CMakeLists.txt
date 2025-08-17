cmake_minimum_required(VERSION 3.15)
project(ChaoticPaper VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(ImageMagick COMPONENTS Magick++ REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(chaoticPaper 
	src/main.cpp
	src/GlyphPattern.cpp
	src/ImageMaker.cpp
	src/WebPattern.cpp
)
target_include_directories(chaoticPaper PRIVATE
	${CMAKE_SOURCE_DIR}/dependencies
	${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(chaoticPaper PRIVATE ImageMagick::Magick++)
