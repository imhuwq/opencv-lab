cmake_minimum_required(VERSION 3.8)
project(panorama_to_cubemap_cpp)

find_package(OpenCV REQUIRED)
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(panorama_to_cubemap_cpp ${SOURCE_FILES})
target_link_libraries(panorama_to_cubemap_cpp ${OpenCV_LIBS})