#include "readline.h"
#include <stdio.h>
#include <stdlib.h>

char *readline(FILE *stream) {
    char *str = NULL;
    int n_char = 0;

    while(1) {
        char c = fgetc(stream);
        if (c == '\r') continue;

        str = realloc(str, sizeof(char) * (n_char + 1));

        // Ler caracteres até achar um espaço (apenas uma palavra)
        if (c == ' ' || c == '\n' || c == EOF) {
            str[n_char] = '\0';
            break;
        }

        str[n_char++] = c;
    }

    return str;
}