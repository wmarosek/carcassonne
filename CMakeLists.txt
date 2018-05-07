cmake_minimum_required(VERSION 3.11)
project(carcassonne C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -Wextra -Wlogical-op -Wdouble-promotion -Wconversion \
    -Wsign-conversion -Wshadow -Wformat=2 -g3 -Wjump-misses-init -pedantic")
include_directories(src)
set(carc_srcs
        src/board.c
        src/board.h
        src/calculator.c
        src/calculator.h
        src/interactive.c
        src/interactive.h
        src/logic.c
        src/logic.h
        src/main.c
        src/point.c
        src/point.h
        src/side.c
        src/side.h
        src/tile.c
        src/tile.h
        src/tlist.c
        src/tlist.h)
add_executable(carcassonne ${carc_srcs})
