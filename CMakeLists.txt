cmake_minimum_required(VERSION 3.14)
project(ffmpeg-asm)

set(CMAKE_C_STANDARD 99)
enable_language(ASM_NASM)

add_library(sse2 INTERFACE IMPORTED)
if(MSVC)
	target_compile_options(sse2 INTERFACE /arch:SSE2)
else()
	target_compile_options(sse2 INTERFACE -msse2)
endif()

string(APPEND CMAKE_ASM_NASM_FLAGS "-DARCH_X86_64=1 -Dprivate_prefix=_ ")

if(WIN32)
	string(APPEND CMAKE_ASM_NASM_FLAGS "-DWIN64=1")
endif(WIN32)

add_library(vec_basic STATIC src/asm/vec_basic.asm)
target_include_directories(vec_basic PRIVATE src/asm)

add_executable(vec_test src/main.c)
target_link_libraries(sse2)
target_link_libraries(vec_test PRIVATE vec_basic)
target_compile_definitions(vec_test PRIVATE TESTS)
