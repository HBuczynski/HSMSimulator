cmake_minimum_required(VERSION 3.0)
project(HSMSimulator)

########################################################################################################
#                                           INITIALIZATION PART                                        #
########################################################################################################

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -pedantic -pthread")


# Set the output folder where the program will be created.
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/target/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/target/lib)

# The following folder will be included
include_directories(src)

#########################################################################################################
#                                           ADDING SUBMODULES                                           #
#########################################################################################################
add_subdirectory("src/time_manager"                                             time_manager            )
add_subdirectory("src/logger"                                                   logger                  )
add_subdirectory("src/utility"                                                  utility                 )
add_subdirectory("src/hsm"                                                      hsm                     )

if((${TARGET_APP} STREQUAL HSMExample))
    add_subdirectory("src/example"                                              example                 )
elseif(${TARGET_APP} STREQUAL AlexaSim)
    add_subdirectory("src/alexa_sim"                                            alexa_sim               )
    add_subdirectory("src/message_queue_wrapper"                                message_queue_wrapper   )
    add_subdirectory("src/interfaces/frame"                                     frame                   )
    add_subdirectory("src/interfaces/commands"                                  commands                )
    add_subdirectory("src/interfaces/responses"                                 responses               )
    add_subdirectory("src/user_mock"                                            user_mock               )
endif()

#########################################################################################################
#                                                   END                                                 #
#########################################################################################################