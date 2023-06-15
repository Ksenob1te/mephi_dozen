cmake_minimum_required(VERSION 3.21)
project(sem1/lab4 C)

set(CMAKE_C_STANDARD 11)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lreadline")

#add_executable(test test/file.c )
# semestr 1
#add_executable(sem1.lab3 sem1/lab3/list_class.c sem1/lab3/main.c)
#add_executable(sem1.2a sem1/2a/file1.c)
#add_executable(sem1.1 sem1/1/file.c)
#add_executable(sem1.lab4 sem1/lab4/main.c sem1/lab4/methods.c)
#add_executable(sem1.5 sem1/5/main.c sem1/5/voter.h sem1/5/voter.c)
#add_executable(sem1.lab5_2 sem1/5/main2.c sem1/5/voter.h sem1/5/voter.c sem1/5/methods.c sem1/5/methods.h)
#add_executable(sem1.lab6 sem1/lab6/main.c sem1/lab6/struct.c sem1/lab6/struct.h)

# semestr 2a
add_executable(1
        1/main.c)

# lab 2a
add_executable(lab2-double
        2a/main.c
        2a/task/input.h
        2a/task/input.c
        2a/task/task.h
        2a/task/task.c
        2a/structs/list.h
        2a/structs/structs.h
        2a/structs/task.h
        2a/structs/source/classes/structs.c
        2a/structs/source/list/doubleList.c
        2a/structs/source/list/doubleList.h)

add_executable(lab2-cycle
        2a/main.c
        2a/task/input.h
        2a/task/input.c
        2a/task/task.h
        2a/task/task.c
        2a/structs/list.h
        2a/structs/structs.h
        2a/structs/task.h
        2a/structs/source/classes/cycleQueue.c
        2a/structs/source/list/cycleList.c
        2a/structs/source/list/cycleList.h)

add_executable(lab2-array
        2a/main.c
        2a/task/input.h
        2a/task/input.c
        2a/task/task.h
        2a/task/task.c
        2a/structs/list.h
        2a/structs/structs.h
        2a/structs/task.h
        2a/structs/source/classes/listQueue.c
        2a/structs/source/list/arrayList.c
        2a/structs/source/list/arrayList.h)

# lab 3

add_executable(3a
        3a/table/table.c
        3a/table/table.h
        3a/methods.c
        3a/methods.h
        3a/main.c
        3a/menu/classic_menu.h
        3a/menu/classic_menu.c)

add_executable(3b
        3b/table/table.c
        3b/table/table.h
        3b/methods.c
        3b/methods.h
        3b/main.c
        3b/menu/classic_menu.h
        3b/menu/classic_menu.c
        3b/file_worker/manager.c
        3b/file_worker/manager.h
        3b/file_worker/removal_list.h)

add_executable(lab3c
        3c/main.c
        3c/table/table.c
        3c/table/table.h
        3c/methods.c
        3c/methods.h
        3c/menu/classic_menu.h
        3c/menu/classic_menu.c)

add_executable(3d
        3d/main.c
        3d/table/table.c
        3d/table/table.h
        3d/file_worker/manager.h
        3d/file_worker/manager.c
        3d/methods.c
        3d/methods.h
        3d/menu/classic_menu.h
        3d/menu/classic_menu.c)

add_executable(4a
        4a/main.c
        4a/menu/classic_menu.h
        4a/menu/classic_menu.c
        4a/tree/tree.c 4a/tree/tree.h 4a/methods.c 4a/methods.h)

add_executable(4b
        4b/main.c
        4b/menu/classic_menu.h
        4b/menu/classic_menu.c
        4b/tree/tree.c 4b/tree/tree.h 4b/main.c 4b/methods.c 4b/methods.h)

add_executable(5
        5/main.c
        5/graph/graph.c
        5/graph/graph.h 5/methods.c 5/methods.h 5/algorthm/search.c 5/algorthm/search.h
        5/menu/classic_menu.c 5/menu/classic_menu.h)

#target_link_libraries(lab4 readline)
