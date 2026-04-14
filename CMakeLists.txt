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
        day7.h
        day7.c
        day8.h
        day8.c
        day9.h
        day9.c
        day10.h
        day10.c
        day11.h
        day11.c
        libs/md5.h
        libs/md5.c
        day9-pq.h
        day9-pq.c
        debug.h
        debug.c
)
