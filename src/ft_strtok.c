#include <minishell.h>

char *ft_strtok(char *str, char *delim) 
{
    static int count = 0;
    int i = count;
    int j = 0;
    char *str2 = NULL;

    while (str[i] != '\0') {
        if (strchr(delim, str[i]) != NULL) 
        {
            i++;
        } 
        else 
        {
            while (str[i] != '\0' && ft_strchr(delim, str[i]) == NULL) 
            {
                i++;
                j++;
            }
            if (j > 0) {
                str2 = (char *)malloc(j + 1); // Aloca memória para a substring
                if (str2 == NULL) {
                    // Lida com erro de alocação de memória, se necessário
                    return NULL;
                }
                strncpy(str2, &str[i - j - 1], j);
                str2[j] = '\0'; // Adiciona o caractere nulo ao final da substring
                count = i;
                return str2;
            }
        }
    }
    return NULL; // Retorna NULL se não houver mais substrings
}


