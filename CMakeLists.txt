# --- WARNING /!\ configuration has been made using msys2 and mingw64 for windows 64 bits /!\ WARNING     ---
# --- WARNING /!\ Qt has been installed with " Qt for open source usage " installer       /!\ WARNING     ---
# --- WARNING /!\ SET msys2/mingw64 and Qt installed directories such as cmake or include /!\ WARNING     ---
# --- WARNING /!\ as system environment variables to be able to compile the project       /!\ END_WARNING ---
                                                                                                            #
cmake_minimum_required(VERSION 3.23)                                                                        #
project(GAME_ENGINE_TEMPLATE)                                                                               #
set(CMAKE_CXX_STANDARD 23)                                                                                  #
set(dir ${CMAKE_CURRENT_SOURCE_DIR})                                                                        #
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${dir}")                                                          #
                                                                                                            #
#==================== SDL2 SETUP ===========================================================================#
                                                                                                            #
find_library(SDL2_LIBRARY SDL2)                                                                             #
if (NOT SDL2_LIBRARY)                                                                                       #
    message(FATAL_ERROR "SDL2 library not found")                                                           #
else ()                                                                                                     #
    message(STATUS "SDL2 library found: ${SDL2_LIBRARY}")                                                   #
endif()                                                                                                     #
                                                                                                            #
message(STATUS "SDL2 include directory found at : ${SDL2_INCLUDE_DIR}")                                     #
find_package(SDL2 REQUIRED)                                                                                 #
include_directories(GAME_ENGINE_TEMPLATE ${SDL2_INCLUDE_DIRS})                                              #
                                                                                                            #
#=================== GLFW SETUP ============================================================================#
                                                                                                            #
find_library(GLFW_LIBRARY glfw3)                                                                            #
if (NOT GLFW_LIBRARY)                                                                                       #
    message(FATAL_ERROR "GLFW library not found")                                                           #
else ()                                                                                                     #
    message(STATUS "GLFW library found: ${GLFW_LIBRARY}")                                                   #
endif()                                                                                                     #
                                                                                                            #
set(GLFW_Include_PATH "C:/msys64/mingw64/include/GLFW")                                                     #
include_directories(GAME_ENGINE_TEMPLATE ${GLFW_Include_PATH})                                              #
message(STATUS "GLFW include directory found at : ${GLFW_Include_PATH}")                                    #
                                                                                                            #
#================= GLEW SETUP ==============================================================================#
                                                                                                            #
find_library(GLEW_LIBRARY glew32)                                                                           #
if (NOT GLEW_LIBRARY)                                                                                       #
    message(FATAL_ERROR "GLEW library not found")                                                           #
else ()                                                                                                     #
    message(STATUS "GLEW library found: ${GLEW_LIBRARY}")                                                   #
endif()                                                                                                     #
                                                                                                            #
set (GLEW_INCLUDE_PATH "C:/msys64/mingw64/include/GL")                                                      #
include_directories(GAME_ENGINE_TEMPLATE ${GLEW_INCLUDE_PATH})                                              #
message(STATUS "GLEW include directory found at : ${GLEW_INCLUDE_PATH}")                                    #
                                                                                                            #
#================= GLAD SETUP ==============================================================================#
                                                                                                            #
add_subdirectory(glad)                                                                                      #
                                                                                                            #
#=============== INCLUSION OF Qt6 ==========================================================================#
                                                                                                            #
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "C:/Qt/6.4.1/mingw81_64/lib/cmake")                             #
set(CMAKE_PREFIX_PATH "C:/Qt/6.4.1/mingw81_64/lib/cmake")                                                   #
message(STATUS "CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}")                                                  #
message(STATUS "CMAKE_PREFIX_PATH = ${CMAKE_PREFIX_PATH}")                                                  #
set(Qt_INCLUDE_PATH "C:/Qt/6.4.1/mingw81_64/include")                                                       #
include_directories(GAME_ENGINE_TEMPLATE ${Qt_INCLUDE_PATH})                                                #
message(STATUS "Qt_INCLUDE_PATH = ${Qt_INCLUDE_PATH}")                                                      #
                                                                                                            #
set(CMAKE_AUTOMOC ON)                                                                                       #
set(CMAKE_AUTORCC ON)                                                                                       #
set(CMAKE_AUTOUIC ON)                                                                                       #
                                                                                                            #
find_package(Qt6 REQUIRED COMPONENTS Widgets Core)                                                          #
if (Qt6_FOUND)                                                                                              #
    message(STATUS "Qt6 found")                                                                             #
else()                                                                                                      #
    message(FATAL_ERROR "Qt6 not found")                                                                    #
endif ()                                                                                                    #
qt_standard_project_setup()                                                                                 #
                                                                                                            #
# --- executable setup and libraries linking ---------------------------------------------------------------#
                                                                                                            #
                                                                                                            #                                                 
add_executable(GAME_ENGINE_TEMPLATE src/main.cpp testing_UI/UI_RENDERER.cpp testing_UI/UI_RENDERER.h)       #                                                         
target_link_libraries(GAME_ENGINE_TEMPLATE ${SDL2_LIBRARY} ${SOURCE_FILES}                                  #
        ${GLFW_LIBRARY} ${GLEW_LIBRARY}                                                                     #
        Qt::Widgets Qt::Core glad)                                                                          #
add_definitions(-DSDL_MAIN_HANDLED)                                                                         #
                                                                                                            #
# --- create directory at root -----------------------------------------------------------------------------#
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/src)                                                                #
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/headers)                                                            #
                                                                                                            #
set_target_properties(GAME_ENGINE_TEMPLATE PROPERTIES                                                       #
        RUNTIME_OUTPUT_DIRECTORY                                                                            #
        ${CMAKE_SOURCE_DIR}/executable)                                                                     #
                                                                                                            #
#============ END OF CMAKE FILE ============================================================================#

