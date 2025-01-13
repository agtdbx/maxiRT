cmake_minimum_required(VERSION 3.0)

project(Libft
    VERSION 0.1
    DESCRIPTION "A simple library of useful functions"
    LANGUAGES C
)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.c)

add_library(libft STATIC ${SOURCES})

target_include_directories(libft PUBLIC include)
target_compile_options(libft PRIVATE -Wall -Wextra -Werror -Ofast)

set_target_properties(libft PROPERTIES OUTPUT_NAME libft)
set_target_properties(libft PROPERTIES PREFIX "")
set_target_properties(libft PROPERTIES SUFFIX ".a")