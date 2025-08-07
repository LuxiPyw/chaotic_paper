cmake_minimum_required(VERSION 3.15)
project(MyProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(ImageMagick COMPONENTS Magick++ REQUIRED)

add_executable(my_app 
	src/main.cpp
	src/glyphs.cpp
	src/config_reader.cpp
	src/makeColorSet.cpp)

target_include_directories(my_app PRIVATE
	${CMAKE_SOURCE_DIR}/dependencies
	${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(my_app PRIVATE ImageMagick::Magick++)
