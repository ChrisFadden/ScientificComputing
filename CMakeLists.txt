cmake_minimum_required(VERSION 2.6)

project(SC)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -fcolor-diagnostics")

#****************
#Enable OpenMP 
#****************
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

#*****************
#Enable MPI
#*****************
find_package(MPI REQUIRED)

include_directories(${MPI_INCLUDE_PATH})
include_directories(${CMAKE_SOURCE_DIR}/include)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/OpenMP)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/MPI)
#add_subdirectory(${CMAKE_SOURCE_DIR}/src/Update)
#add_subdirectory(${CMAKE_SOURCE_DIR}/src/Process)
#add_subdirectory(${CMAKE_SOURCE_DIR}/src/PML)

add_executable(SC ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_link_libraries(SC OpenMPlib MPIlib ${MPI_LIBRARIES})

if(MPI_COMPILE_FLAGS)
  set_target_properties(SC PROPERTIES
    COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif()

if(MPI_LINK_FLAGS)
  set_target_properties(SC PROPERTIES
    LINK_FLAGS "${MPI_LINK_FLAGS}")
endif()


