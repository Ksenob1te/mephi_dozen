#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
int getch(void) {
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}
#endif

#define MAX_OPTIONS 3

int main() {
    int selected_option = 0;
    int key_code;

    while (1) {
        system("cls||clear");
        printf("Use arrow keys to navigate the menu and press Enter to select an option.\n\n");

        for (int i = 0; i < MAX_OPTIONS; i++) {
            if (i == selected_option) printf("> ");
            else printf("  ");
            printf("Option %d\n", i + 1);
        }

        key_code = getch();

#ifdef _WIN32
        if (key_code == 224) key_code = getch();
#endif

        switch (key_code) {
            case 'w':
            case 'W':
            case 72:
                selected_option--;
                break;
            case 's':
            case 'S':
            case 80:
                selected_option++;
                break;
            case '\r':
                printf("\nOption %d selected!\n", selected_option + 1);
                getch();
                break;
        }

        if (selected_option >= MAX_OPTIONS) selected_option = MAX_OPTIONS - 1;
        else if (selected_option < 0) selected_option = 0;

    }
    return EXIT_SUCCESS;
}