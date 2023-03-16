#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <windows.h>

// LXSoft
// mod: cui/menu_021
// stdarg.h  -> used for variable list of arguments (va_list, va_start ...)
// windows.h -> used for Sleep function, for *nix use unistd.h

typedef unsigned short int usint_t;
// Menu function prototype
int menu(char* name, char* prefix, char* cursor, usint_t orientation,
         usint_t padding, usint_t start_pos, usint_t delay,
         usint_t num_childs, ...);

int main()
{
    int response = menu("OPTIONS","[*]","->",1,3,3,0,5,
                        "PROFILES","ACTIVITY","VIDEO","SOUND","GAMEPLAY");
    switch(response)
    {
        case 1:
            // doSomethingFoo1();
            break;
        case 2:
            //doSomethingFoo2();
            break;
            /*
             * .
             * .
             * .
             * case n:
             * break;
             */
    }
    printf("\nYour choice is: %d", response);
    return 0;
}

// Menu implementation
int menu
        (
                char *name,        // Menu name (eg.: OPTIONS)
                char *prefix,      // Menu prefix (eg.: [*])
                char *cursor,      // Menu cursor (eg.: ->)
                usint_t orient,    /*
                        * Menu orientation vertical or horzontal.
                        * 0 or false for horizontal
                        * 1 or true for vertical
                        */
                usint_t padding,   // Menu childrens padding (eg.: 3)
                usint_t start_pos, // Menu set active child (eg.: 1)
                usint_t delay,     // Menu children switch delay
                usint_t childs,    // Number of childrens
                ...                /*
                        * Variable list of arguments char* type.
                        * Name of the childrens.
                        */
        )
{
    va_list args;
    int tmp=0,pos;
    char chr;
    usint_t opt=start_pos;
    char* format=malloc
            (
                    (
                            strlen(name)+strlen(prefix)+strlen(cursor)+
                            3+ /* menu suffix (1 byte) and backspace (2 bytes) */
                            (2*childs)+ /* newline (2 bytes) times childs */
                            (padding*childs)+ /* number of spaces times childs */
                            childs*15 /* children name maxlen (15 bytes) times childs*/
                    )*sizeof(char)
            );
    do
    {
        if(tmp!=0)chr=getch();
        if(chr==0x48||chr==0x4B)
            (opt>1&&opt!=1)?opt--:(opt=childs);
        else if(chr==0x50||chr==0x4D)
            (opt>=1&&opt!=childs)?opt++:(opt=1);
        else {/* do nothing at this time*/}
        strcpy(format,"");
        strcat(format,prefix);
        strcat(format,name);
        strcat(format,":");
        va_start(args,childs);
        for (tmp=1;tmp<=childs;tmp++)
        {
            (orient)?strcat(format,"\n"):0;
            pos=padding;
            while((pos--)>0) strcat(format," ");
            if(tmp==opt)
            {
                strcat(format,"\b");
                strcat(format,cursor);
            }
            strcat(format,va_arg(args,char*));
        }
        /*if(tmp!=childs)
        {
            fprintf(stderr,"%s: recieved NULL pointer argument,"
                           " child not named", __func__);
            return -1;
        }*/
        Sleep(delay);
        system("cls");
        printf(format);
        va_end(args);
    }while((chr=getch())!=0x0D);
    return opt;
}