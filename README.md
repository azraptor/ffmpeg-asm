# FFmpeg Assembly Stuffs
A project to learn how to program in x86_64 assembly the way video and audio devs do it.

Largely following [this](https://github.com/FFmpeg/asm-lessons) well written tutorial by the FFMpeg team.

## Building

### With Make

This will *only* work on Linux.

Install the following `nasm gcc make`, use your favorite package manager.

Execute `make` to build the program.

Run the program like so `./out/vec_test`

### With CMake

This should work on both Linux and Windows.

Install nasm, a C compiler, and cmake. Then open up a terminal.

Create a new directory and enter into it by running `mkdir build` and `cd build`.

Run `cmake ..` to generate build files.

Build program by running `cmake --build .`

Run the program like so `./vec_test`

<br>
More shall be added at some point.
