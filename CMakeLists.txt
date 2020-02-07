cmake_minimum_required(VERSION 3.14)
project(zasm
    VERSION 1.0.0
    DESCRIPTION "A framework for learning Z80 assembler programming"
)

add_library(zasm
    src/meta.hh

    include/zasm/types.hh
    include/zasm/registers.hh src/registers.cc

    include/zasm/machine/bus.hh src/machine/bus.cc
    include/zasm/machine/cpu.hh src/machine/cpu.cc
    src/machine/instructions.hh
)

target_compile_features(zasm
    PUBLIC
        cxx_std_17
)

target_include_directories(zasm
    SYSTEM INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${CMAKE_CURRENT_LIST_DIR}/src
)

target_compile_options(zasm
    PRIVATE
        $<IF:$<CXX_COMPILER_ID:MSVC>,/WX /W4,-Wall -Wextra -Wpedantic -Werror>
)
