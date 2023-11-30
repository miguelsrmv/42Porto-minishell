#include <stdio.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int main (int argc, char **argv)
{
    int i;

    (void)argc;
    i = ft_strcmp(argv[1], argv[2]);
    printf("%i\n", i);
    return (0);
}