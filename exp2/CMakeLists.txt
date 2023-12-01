cmake_minimum_required(VERSION 3.27)
project(OSExperiment)

set(CMAKE_C_STANDARD 99)

add_executable(OSExperiment exp2-4.c
        exp2-2.nowait.c
        exp2-1.c
        exp2-2.withwait.c
        exp2-5.c
        exp2-6.deadlock.c
        exp2-6.nodeadlock.c
        exp2-6.nodeadlock.c)
