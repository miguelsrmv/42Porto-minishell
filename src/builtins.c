# include "minishell.h"

/* void    ft_builtins(char *str)
{
    if(str = "pwd")
        execute_pwd(str);
} */

void    execute_pwd(char *str)
{
	shell->pwd = getcwd(pwd, 0);
	printf("%s\n", shell->pwd);
}