cmake_minimum_required(VERSION 4.1)
project(aoc_2015 C)

set(CMAKE_C_STANDARD 23)

add_executable(aoc_2015 main.c
        helpers.h
        day1.h
        day1.c
        days.h
        day2.h
        day2.c
        day3.c
        day3.h
        day4.h
        day4.c
        day5.h
        day5.c
        day6.h
        day6.c
        libs/md5.h
        libs/md5.c
)
