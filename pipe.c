#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_words(char *str)
{
    int i = 0;
    int word = 0;
    while(str[i] != '\0')
    {
        while(str[i] == ' ' || str[i] == '\t')
            i++;
        while(str[i] != ' ' && str[i] != '\t' && str[i] != '|' && str[i] != '\0')
            i++;
        word++;
        if(str[i] == '|')
        {
            i++;
            word++;   
        }
    }
    return (word);
}

char   **ft_pipe(char *str)
{
    char **new;
    int i = 0;
    int j = 0;
    int h = 0;
    int words;
    int word_len = 0;

    words = count_words(str);
    new = (char **)malloc((words + 1) * sizeof(char *));

    while(str[i] != '\0')
    {
        word_len
        while(str[i] == ' ' || str[i] == '\t')
            i++;
        while(str[i] != ' ' && str[i] != '\t' && str[i] != '|' && str[i] != '\0')
        {
            word_len++;
            i++;
        }
        new[j] = (char *)malloc(word_len + 1);
        i = i - word_len;
        h = 0;
        while(str[i] != ' ' && str[i] != '\t' && str[i] != '|' && str[i] != '\0')
        {
            new[j][h] = str[i];
            i++;
            h++;
        }
        new[j][h] = '\0';
        j++;
        if(str[i] == '|')
        {
            new[j] = (char *)malloc(2);
            new[j][0] = '|';
            new[j][1] = '\0';
            i++;
            j++;
        }
    }
    new[j] = NULL;
    return (new);
}

int main(int ac, char **av)
{
    char **new;
    int i = 0;
    int j = 0;

    if(ac == 2)
    {
        new = ft_pipe(av[1]);
        while(new[i] != NULL)
        {
            printf("[%s]", new[i]);
            i++;
        }
    }
    return (0);
}