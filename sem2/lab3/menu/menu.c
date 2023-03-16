#include <stdio.h>
#include <conio.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int main()
{
    int option = 1; // текущий выбранный вариант
    int key; // код нажатой клавиши
    char *menu[4] = {"Option 1", "Option 2", "Option 3", "Option 4"}; // массив строк с названиями вариантов

    do {
        system("cls"); // очистить экран

        for (int i = 0; i < 4; i++) {
            if (i == option - 1) {
                printf("> %s\n", menu[i]); // вывести выбранный вариант с символом >
            } else {
                printf(" %s\n", menu[i]); // вывести остальные варианты без символа >
            }
        }

        key = getch(); // получить код нажатой клавиши

        if (key == 224 || key == 0) { // если это специальная клавиша
            key = getch(); // получить следующий код

            switch (key) { // обработать коды стрелок
                case UP:
                    option--; // перейти к предыдущему варианту
                    if (option < 1) option = 4; // если вышли за границу меню, вернуться к последнему варианту
                    break;
                case DOWN:
                    option++; // перейти к следующему варианту
                    if (option > 4) option = 1; // если вышли за границу меню, вернуться к первому варианту
                    break;
                case LEFT:
                case RIGHT:
                    printf("\nYou selected %s\n", menu[option - 1]); // вывести выбранный вариант на экран
                    break;
            }
        }

    } while (key != '\r'); // повторять цикл до тех пор, пока не будет нажата клавиша Enter

    return 0;
}