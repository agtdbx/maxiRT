cmake_minimum_required(VERSION 3.0)

project(Ffmpeg
    VERSION 0.1
    DESCRIPTION "Video and audio processing library"
    LANGUAGES C
)

# already compiled .so files

add_library(ffmpeg INTERFACE)

# make it a system include
target_include_directories(
    ffmpeg INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
target_link_directories(
    ffmpeg INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}"
)

