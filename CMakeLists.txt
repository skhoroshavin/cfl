cmake_minimum_required(VERSION 3.4)
project(cfl)

option(CFL_GEN_COVERAGE "Generate tests coverage information" OFF)
if (CFL_GEN_COVERAGE)
    set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} --coverage)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} --coverage)
endif (CFL_GEN_COVERAGE)

add_library(cfl_core
    src/core/utils.h
    src/core/utils.c
    src/core/memory.h
    src/core/memory.c
    src/core/list.h
    src/core/list.c
    src/core/string_list.h
    src/core/string_list.c
    src/core/logger.h
    src/core/logger.c)
target_include_directories(cfl_core INTERFACE src)
if (NOT MSVC)
    target_compile_options(cfl_core PRIVATE -Wall -Wextra -Werror)
endif (NOT MSVC)

add_library(cfl_test
    src/test/context.h
    src/test/context.c
    src/test/asserts.h
    src/test/test.h
    src/test/test.c)
target_link_libraries(cfl_test PUBLIC cfl_core)
target_include_directories(cfl_test INTERFACE src)
if (NOT MSVC)
    target_compile_options(cfl_test PRIVATE -Wall -Wextra -Werror)
endif (NOT MSVC)

add_executable(tests
    tests/test_common.h
    tests/test_common.c
    tests/test_main.c
    tests/core/test_utils.c
    tests/core/test_memory.c
    tests/core/test_list.c
    tests/core/test_string_list.c
    tests/core/test_logger.c
    tests/test/test_context.c
    tests/test/test_asserts.c
    tests/test/test_test.c)
target_link_libraries(tests cfl_test)
if (NOT MSVC)
    target_compile_options(tests PRIVATE -Wall -Wextra -Werror)
endif (NOT MSVC)
