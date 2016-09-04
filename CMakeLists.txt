cmake_minimum_required(VERSION 2.6)

project(SC)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic")

#Enable OpenMP parallelism
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

include_directories(${CMAKE_SOURCE_DIR}/include)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/OpenMP)
#add_subdirectory(${CMAKE_SOURCE_DIR}/src/Error)
#add_subdirectory(${CMAKE_SOURCE_DIR}/src/Update)
#add_subdirectory(${CMAKE_SOURCE_DIR}/src/Process)
#add_subdirectory(${CMAKE_SOURCE_DIR}/src/PML)

add_executable(SC ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_link_libraries(SC OpenMPlib)
