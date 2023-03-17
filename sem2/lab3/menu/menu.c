#include <stdio.h>
#include <termios.h>
#include <unistd.h>

struct termios saved_attributes;

void reset_input_mode (void)
{
    tcsetattr (STDIN_FILENO, TCSANOW, &saved_attributes);
}

void set_input_mode (void)
{
    struct termios tattr;

    /* Make sure stdin is a terminal. */
    if (!isatty (STDIN_FILENO))
    {
        fprintf (stderr, "Not a terminal.\n");
        exit (EXIT_FAILURE);
    }

    /* Save the terminal attributes so we can restore them later. */
    tcgetattr (STDIN_FILENO, &saved_attributes);
    atexit (reset_input_mode);

    /* Set the funny terminal modes. */
    tcgetattr (STDIN_FILENO, &tattr);
    tattr.c_lflag &= ~(ICANON|ECHO); /* Clear ICANON and ECHO. */
    tattr.c_cc[VMIN] = 1;
    tattr.c_cc[VTIME] = 0;
    tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);
}

// Функция для отображения меню и выделения текущего пункта
void display_menu(int current)
{
    char *menu[] = {"Пункт 1", "Пункт 2", "Пункт 3", "Выход"};
    int size = sizeof(menu) / sizeof(menu[0]);

    printf("\033[H\033[J"); // Очистить экран
    printf("Выберите пункт меню:\n");

    for (int i = 0; i < size; i++)
    {
        if (i == current) // Если текущий пункт - выделить его цветом
        {
            printf("\033[30;47m%s\033[0m\n", menu[i]); // Черный текст на белом фоне
        }
        else // Иначе - обычный текст
        {
            printf("%s\n", menu[i]);
        }

    }
}

// Функция для обработки выбора пользователя
void handle_choice(int choice)
{
    switch (choice)
    {
        case 0:
            printf("Вы выбрали пункт 1\n");
            break;
        case 1:
            printf("Вы выбрали пункт 2\n");
            break;
        case 2:
            printf("Вы выбрали пункт 3\n");
            break;
        case 3:
            printf("Вы выбрали выход\n");
            break;
        default:
            printf("Неверный выбор\n");
            break;
    }
}

int main()
{
    int current = 0; // Текущий выбранный пункт меню
    int done = 0; // Флаг завершения программы
    char c; // Символ для чтения ввода

    set_input_mode(); // Установить режим небуферизованного ввода

    display_menu(current); // Отобразить меню

    while (!done) // Пока не завершено
    {
        c = getchar(); // Прочитать символ

        if (c == '\033') // Если символ - escape
        {
            getchar(); // Пропустить следующий символ '['
            c = getchar(); // Прочитать код клавиши со стрелкой

            switch (c)
            {
                case 'A': // Если вверх
                    current--; // Уменьшить текущий выбор на 1
                    if (current < 0) current = 0; // Не выходить за границы меню
                    break;
                case 'B': // Если вниз
                    current++; // Увеличить текущий выбор на 1
                    if (current > 3) current = 3; // Не выходить за границы меню
                    break;
                default:
                    break;
            }

            display_menu(current); // Отобразить меню с новым выбором

        }
        else if (c == '\n') // Если символ - enter
        {
            handle_choice(current); // Обработать выбор пользователя

            if (current == 3) done = 1; // Если выбран выход - завершить программу

        }

    }
    reset_input_mode ();

    return 0;
}