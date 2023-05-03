cmake_minimum_required(VERSION 3.21)
project(sem1/lab4 C)

set(CMAKE_C_STANDARD 11)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lreadline")

add_executable(test test/file.c )
# semestr 1
add_executable(sem1.lab3 sem1/lab3/list_class.c sem1/lab3/main.c)
add_executable(sem1.lab2 sem1/lab2/file1.c)
add_executable(sem1.lab1 sem1/lab1/file.c)
add_executable(sem1.lab4 sem1/lab4/main.c sem1/lab4/methods.c)
add_executable(sem1.lab5 sem1/lab5/main.c sem1/lab5/voter.h sem1/lab5/voter.c)
add_executable(sem1.lab5_2 sem1/lab5/main2.c sem1/lab5/voter.h sem1/lab5/voter.c sem1/lab5/methods.c sem1/lab5/methods.h)
add_executable(sem1.lab6 sem1/lab6/main.c sem1/lab6/struct.c sem1/lab6/struct.h)

# semestr 2
add_executable(sem2.lab1
        sem2/lab1/main.c)

# lab 2
add_executable(sem2.lab2-double
        sem2/lab2/main.c
        sem2/lab2/task/input.h
        sem2/lab2/task/input.c
        sem2/lab2/task/task.h
        sem2/lab2/task/task.c
        sem2/lab2/structs/list.h
        sem2/lab2/structs/structs.h
        sem2/lab2/structs/task.h
        sem2/lab2/structs/source/classes/structs.c
        sem2/lab2/structs/source/list/doubleList.c
        sem2/lab2/structs/source/list/doubleList.h)

add_executable(sem2.lab2-cycle
        sem2/lab2/main.c
        sem2/lab2/task/input.h
        sem2/lab2/task/input.c
        sem2/lab2/task/task.h
        sem2/lab2/task/task.c
        sem2/lab2/structs/list.h
        sem2/lab2/structs/structs.h
        sem2/lab2/structs/task.h
        sem2/lab2/structs/source/classes/cycleQueue.c
        sem2/lab2/structs/source/list/cycleList.c
        sem2/lab2/structs/source/list/cycleList.h)

add_executable(sem2.lab2-array
        sem2/lab2/main.c
        sem2/lab2/task/input.h
        sem2/lab2/task/input.c
        sem2/lab2/task/task.h
        sem2/lab2/task/task.c
        sem2/lab2/structs/list.h
        sem2/lab2/structs/structs.h
        sem2/lab2/structs/task.h
        sem2/lab2/structs/source/classes/listQueue.c
        sem2/lab2/structs/source/list/arrayList.c
        sem2/lab2/structs/source/list/arrayList.h)

# lab 3

add_executable(sem2.lab3
        sem2/lab3/table/table.c
        sem2/lab3/table/table.h
        sem2/lab3/methods.c
        sem2/lab3/methods.h
        sem2/lab3/main.c
        sem2/lab3/menu/classic_menu.h
        sem2/lab3/menu/classic_menu.c
        sem2/lab3/file_worker/manager.c
        sem2/lab3/file_worker/manager.h
        sem2/lab3/file_worker/removal_list.h)

add_executable(sem2.lab3c
        sem2/lab3с/main.c
        sem2/lab3с/table/table.c
        sem2/lab3с/table/table.h
        sem2/lab3с/methods.c
        sem2/lab3с/methods.h
        sem2/lab3с/menu/classic_menu.h
        sem2/lab3с/menu/classic_menu.c)

add_executable(sem2.lab3d
        sem2/lab3d/main.c
        sem2/lab3d/table/table.c
        sem2/lab3d/table/table.h
        sem2/lab3d/file_worker/manager.h
        sem2/lab3d/file_worker/manager.c
        sem2/lab3d/methods.c
        sem2/lab3d/methods.h
        sem2/lab3d/menu/classic_menu.h
        sem2/lab3d/menu/classic_menu.c)

#target_link_libraries(lab4 readline)