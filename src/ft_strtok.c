char    ft_strtok(char *str, char *a)
{
    static int count = 0;
    int i = 0;
    int j = 0;
    int x = 0;
    char *str2;

    while(x < count)
    {
        j = 0;
        if(str[i] == a)
            i++;
        while(str[i] != a)
        {
            str2[j] = str[i];
            i++;
            j++;
        }
        x++;
    }
    return (str2);

}