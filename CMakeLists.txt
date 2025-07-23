cmake_minimum_required(VERSION 3.10)
project(AutoPlayMusic LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

add_library(miniaudio STATIC ${SRC_DIR}/miniaudio/miniaudio.c)
target_include_directories(miniaudio PUBLIC ${SRC_DIR})

set(SOURCES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/folder.cpp
    ${SRC_DIR}/play.cpp
    ${SRC_DIR}/rng.cpp
)

set(HEADERS
    ${SRC_DIR}/folder.hpp
    ${SRC_DIR}/play.hpp
    ${SRC_DIR}/rng.hpp
)

add_executable(AutoPlayMusic ${SOURCES} ${HEADERS})

target_link_libraries(AutoPlayMusic PRIVATE miniaudio)
