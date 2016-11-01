cmake_minimum_required(VERSION 2.8)
project(particle-swarm)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
set(SDL2_DIR "${PROJECT_SOURCE_DIR}/deps/SDL2-2.0.5")

if(MINGW)
    set(SDL2_LIBRARY mingw32 SDL2main SDL2)
    set(SDL2_INCLUDE_DIR "${SDL2_DIR}/include")
    link_directories("${SDL2_DIR}/lib/mingw32")
elseif(WIN32)
    set(SDL2_LIBRARY SDL2main SDL2)
    set(SDL2_INCLUDE_DIR "${SDL2_DIR}/include")
    link_directories("${SDL2_DIR}/lib/win32")
else()
    find_package(SDL2 REQUIRED)
endif()

set(SOURCES
    src/main.cpp
)

add_executable(particle ${SOURCES})

include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(particle ${SDL2_LIBRARY})
