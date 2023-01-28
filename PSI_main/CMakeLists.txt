#project(PSI_main) 

#############################################
#               Build PSI_main             #
#############################################

file(GLOB_RECURSE SRCS_TEST ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(PSI_main STATIC ${SRCS_TEST})

#############################################
#            Link our libraries             #
#############################################
target_link_libraries(PSI_main PSI)
