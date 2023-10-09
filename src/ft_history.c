#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<readline/readline.h>
#include<readline/history.h>

int ft_history (char *var)
{
    using_history ();
    add_history (var);
    //add_history ("Mais qualquer coisa");
    HIST_ENTRY** historia = history_list();
    HIST_ENTRY *coiso = history_get(1);
    return(0);
}
