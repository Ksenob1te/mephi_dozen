cmake_minimum_required(VERSION 3.21)
project(lab4 C)

set(CMAKE_C_STANDARD 11)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lreadline")

add_executable(test test/file.c )
# semestr 1
add_executable(lab3 lab3/list_class.c lab3/main.c)
add_executable(lab2 lab2/file1.c)
add_executable(lab1 lab1/file.c)
add_executable(lab4 lab4/main.c lab4/methods.c)
add_executable(lab5 lab5/main.c lab5/voter.h lab5/voter.c)
add_executable(lab5_2 lab5/main2.c lab5/voter.h lab5/voter.c lab5/methods.c lab5/methods.h)
add_executable(lab6 lab6/main.c lab6/struct.c lab6/struct.h)
