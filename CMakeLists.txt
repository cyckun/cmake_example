cmake_minimum_required(VERSION 3.4...3.18)
project(cmake_example)


include_directories("${CMAKE_SOURCE_DIR}")

# set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)
# set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib)
# set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib)

# message("test path -------------")
# message( ${CMAKE_HOME_DIRECTORY})

#############################################
#            Flag and #defines              #
#############################################
add_definitions(-DSOLUTION_DIR=\"${CMAKE_SOURCE_DIR}\")
set(CMAKE_C_FLAGS "-ffunction-sections  -Wno-strict-aliasing  -maes -msse2 -msse4.1 -mpclmul -Wno-sign-compare -Wfatal-errors -pthread")
set(CMAKE_CXX_FLAGS  "${CMAKE_C_FLAGS}  -std=c++14")

# Set a default build type for single-configuration
# CMake generators if no build type is set.
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
   SET(CMAKE_BUILD_TYPE Release)
endif()


if(NOT ${CMAKE_BUILD_TYPE} STREQUAL "Release")
  message(WARNING "\nConfiguration NOT set to Release. Please call cmake with -DCMAKE_BUILD_TYPE=Release  instead of ${CMAKE_BUILD_TYPE}")

    if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
      message(WARNING "Debug build.")
    elseif("${CMAKE_BUILD_TYPE}" STREQUAL "Release") 
      message(WARNING "Release build.")
    elseif("${CMAKE_BUILD_TYPE}" STREQUAL  "RELWITHDEBINFO")
      message(WARNING "RELWITHDEBINFO=Release with debug info build.")
    else()
      message(ERROR ": Unknown build type - ${CMAKE_BUILD_TYPE}  Please use one of Debug, Release, or RELWITHDEBINFO\n\n" )
    endif()
endif()


# Select flags.
SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g -ggdb -rdynamic")
SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g3 -ggdb -rdynamic")
# 
#############################################
#       Library/includes locations          #
#############################################

include_directories("${CMAKE_SOURCE_DIR}")

# default location for libOTe
set(libOTe_Dirs "${CMAKE_SOURCE_DIR}/psi_libote/")
include_directories("${libOTe_Dirs}/") 
include_directories("${libOTe_Dirs}/libOTe") 
include_directories("${libOTe_Dirs}/cryptoTools")

# default location for miracl
set(Miracl_Dirs "${libOTe_Dirs}/cryptoTools/thirdparty/linux/miracl/")
include_directories("${Miracl_Dirs}") 

# default location for Boost
set(BOOST_ROOT "${libOTe_Dirs}/cryptoTools/thirdparty/linux/boost/")


# #############################################
# #               Build PSI                   #
# #############################################


set(CMAKE_POSITION_INDEPENDENT_CODE ON)
 
add_subdirectory(pybind11)

add_subdirectory(PSI)
add_subdirectory(PSI_test)

pybind11_add_module(cmake_example src/main.cpp)

target_link_libraries(cmake_example PUBLIC PSI_test)
target_include_directories(cmake_example PUBLIC PSI_test)


# EXAMPLE_VERSION_INFO is defined by setup.py and passed into the C++ code as a
# define (VERSION_INFO) here.
target_compile_definitions(cmake_example
                           PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})