cmake_minimum_required(VERSION 3.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(MaxiRT
    VERSION 0.1
    DESCRIPTION "A simple raytracer"
    LANGUAGES C
)

add_subdirectory(lib/mlx42)
add_subdirectory(lib/libft)
add_subdirectory(lib/ffmpeg)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.c)

add_executable(MaxiRT ${SOURCES})

set_target_properties(MaxiRT PROPERTIES
    RUNTIME_OUTPUT_NAME rt
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)

target_include_directories(MaxiRT PRIVATE src)
target_compile_options(MaxiRT PRIVATE
    -Wall -Wextra -Werror
    -std=gnu99 -Wunreachable-code -Ofast
)
target_link_directories(MaxiRT PRIVATE lib/ffmpeg)
target_link_options(MaxiRT PRIVATE
    -Ofast -flto
)
target_link_libraries(MaxiRT
    libft
    mlx42 dl glfw pthread m
    ffmpeg swresample avcodec avutil swscale
)
