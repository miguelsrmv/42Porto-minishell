#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<readline/readline.h>
#include<readline/history.h>

int main (void)
{
    using_history ();
    add_history ("Qualquer coisa");
    add_history ("Mais qualquer coisa");
    HIST_ENTRY** historia = history_list();
    HIST_ENTRY *coiso = history_get(1);
}
