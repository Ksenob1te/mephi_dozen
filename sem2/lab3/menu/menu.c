#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include "stdlib.h"


// IDK how it works but it works
// >-=============================-<
struct termios saved_attributes;

void reset_input_mode(void) {
    tcsetattr(STDIN_FILENO, TCSANOW, &saved_attributes);
}

void set_input_mode(void) {
    struct termios tattr;

    /* Make sure stdin is a terminal. */
    if (!isatty(STDIN_FILENO)) {
        fprintf(stderr, "Not a terminal.\n");
        exit(EXIT_FAILURE);
    }

    /* Save the terminal attributes so we can restore them later. */
    tcgetattr(STDIN_FILENO, &saved_attributes);
    atexit(reset_input_mode);

    /* Set the funny terminal modes. */
    tcgetattr(STDIN_FILENO, &tattr);
    tattr.c_lflag &= ~(ICANON | ECHO);
    tattr.c_cc[VMIN] = 1;
    tattr.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &tattr);
}
// >-=============================-<


void display_menu(int current) {
    char *menu[] = {"Пункт 1", "Пункт 2", "Пункт 3", "Выход"};
    int size = sizeof(menu) / sizeof(menu[0]);

    printf("\033[H\033[J");
    printf("Выберите пункт меню:\n");

    for (int i = 0; i < size; i++) {
        if (i == current) {
            printf("\033[30;47m%s\033[0m\n", menu[i]);
        } else {
            printf("%s\n", menu[i]);
        }

    }
}

void handle_choice(int choice) {
    int data;
    switch (choice) {
        case 0:
            scanf("%d", &data);
            printf("Выполнение пункта 1, дата: %d\n", data);
            break;
        case 1:
            printf("Вы выбрали пункт 2\n");
            break;
        case 2:
//            printf("Вы выбрали пункт 3\n");
            break;
        case 3:
            printf("Вы выбрали выход\n");
            break;
        default:
            printf("Неверный выбор\n");
            break;
    }
}

int main() {
    int current = 0;
    int done = 0;
    char c;

    set_input_mode();
    display_menu(current);

    while (!done) {
        printf("RESTART DONE\n");
        c = getchar();
        if (c == '\033') {
            getchar();
            c = getchar();

            switch (c) {
                case 'A':
                    current--;
                    if (current < 0) current = 0;
                    break;
                case 'B':
                    current++;
                    if (current > 3) current = 3;
                    break;
                default:
                    break;
            }

            display_menu(current);

        } else if (c == '\n') {
            reset_input_mode();
            handle_choice(current);
            if (current == 3) {done = 1;}
            set_input_mode();
            scanf("%*[\n]");
        }
    }
    reset_input_mode();

    return 0;
}