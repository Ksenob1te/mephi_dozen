cmake_minimum_required(VERSION 3.21)
project(sem1/lab4 C)

set(CMAKE_C_STANDARD 11)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lreadline")

add_executable(test test/file.c )
# semestr 1
#add_executable(sem1.lab3 sem1/lab3/list_class.c sem1/lab3/main.c)
#add_executable(sem1.lab2 sem1/lab2/file1.c)
#add_executable(sem1.lab1 sem1/lab1/file.c)
#add_executable(sem1.lab4 sem1/lab4/main.c sem1/lab4/methods.c)
#add_executable(sem1.lab5 sem1/lab5/main.c sem1/lab5/voter.h sem1/lab5/voter.c)
#add_executable(sem1.lab5_2 sem1/lab5/main2.c sem1/lab5/voter.h sem1/lab5/voter.c sem1/lab5/methods.c sem1/lab5/methods.h)
#add_executable(sem1.lab6 sem1/lab6/main.c sem1/lab6/struct.c sem1/lab6/struct.h)

# semestr 2
add_executable(lab1
        lab1/main.c)

# lab 2
add_executable(lab2-double
        lab2/main.c
        lab2/task/input.h
        lab2/task/input.c
        lab2/task/task.h
        lab2/task/task.c
        lab2/structs/list.h
        lab2/structs/structs.h
        lab2/structs/task.h
        lab2/structs/source/classes/structs.c
        lab2/structs/source/list/doubleList.c
        lab2/structs/source/list/doubleList.h)

add_executable(lab2-cycle
        lab2/main.c
        lab2/task/input.h
        lab2/task/input.c
        lab2/task/task.h
        lab2/task/task.c
        lab2/structs/list.h
        lab2/structs/structs.h
        lab2/structs/task.h
        lab2/structs/source/classes/cycleQueue.c
        lab2/structs/source/list/cycleList.c
        lab2/structs/source/list/cycleList.h)

add_executable(lab2-array
        lab2/main.c
        lab2/task/input.h
        lab2/task/input.c
        lab2/task/task.h
        lab2/task/task.c
        lab2/structs/list.h
        lab2/structs/structs.h
        lab2/structs/task.h
        lab2/structs/source/classes/listQueue.c
        lab2/structs/source/list/arrayList.c
        lab2/structs/source/list/arrayList.h)

# lab 3

add_executable(lab3
        lab3/table/table.c
        lab3/table/table.h
        lab3/methods.c
        lab3/methods.h
        lab3/main.c
        lab3/menu/classic_menu.h
        lab3/menu/classic_menu.c
        lab3/file_worker/manager.c
        lab3/file_worker/manager.h
        lab3/file_worker/removal_list.h)

add_executable(lab3c
        lab3с/main.c
        lab3с/table/table.c
        lab3с/table/table.h
        lab3с/methods.c
        lab3с/methods.h
        lab3с/menu/classic_menu.h
        lab3с/menu/classic_menu.c)

add_executable(lab3d
        lab3d/main.c
        lab3d/table/table.c
        lab3d/table/table.h
        lab3d/file_worker/manager.h
        lab3d/file_worker/manager.c
        lab3d/methods.c
        lab3d/methods.h
        lab3d/menu/classic_menu.h
        lab3d/menu/classic_menu.c)

add_executable(lab4a
        lab4a/main.c
        lab4a/menu/classic_menu.h
        lab4a/menu/classic_menu.c
        lab4a/tree/tree.c lab4a/tree/tree.h lab4a/methods.c lab4a/methods.h)

#target_link_libraries(lab4 readline)
