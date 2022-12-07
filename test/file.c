#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#define DELIM " \t"

short check(char *str1, char *str2) {
    int count=0;
    for (int i=0;i<strlen(str1);i++) {
        for (int j=0;j<strlen(str2);j++) {
            if (str1[i]==str2[j]) {
                count+=1;
                break;
            }
        }
    }
    if (count==strlen(str1)) return 1;
    return 0;
}


char* registr(char *str1) {
    char* buff=calloc(strlen(str1)+1, sizeof(char));
    for (int i=0; i<=strlen(str1);i++){


        if((int) str1[i] >= 65 && (int) str1[i] <= 90){
            buff[i] = (char) ((int) str1[i] + 32);
        }
        else buff[i]=str1[i];
    }
    return buff;
}

void editor(char  *str){
    int res_len=0;
    char **res=calloc(res_len+1, sizeof(char*));
    char *word=strtok(str, DELIM);
    while (word!=NULL){
        res[res_len] = word;
        res_len+=1;
        res= realloc(res,(res_len+1) * sizeof(char*));
        word=strtok(NULL, DELIM);
    }
    for (int i=0;i<res_len;i++) {
        for (int j=i+1;j<res_len;j++) {
            if (check(registr(res[i]), registr(res[j]))==1) {
                char *buff=res[j];
                for (int g=j-1 ; g>i; g--){
                    res[g+1]=res[g];
                }
                res[i+1]=buff;
            }
        }
    }
    for (int i=0; i<res_len;i++){
        printf("%s", res[i]);
    }
}

int main(){
    char *s=readline("> ");
//    char *pshol=strtok(s," \t");
    printf("%s\n", s);
    while (s != NULL){
        printf("\"%s\"\n", s);
        editor(s);
        free(s);
        s=readline("> ");
    }
    return 0;
}