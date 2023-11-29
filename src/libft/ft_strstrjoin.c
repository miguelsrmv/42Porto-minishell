#include "libft.h"

char	*ft_strstrjoin(char *s1, char *s2, char *divider)
{
	char	*out;
	int		i;
	int		j;

	if (!s1)
		return (NULL);
	i = 0;
	j = 0;
	s1 = ft_append(&s1, divider);
	out = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (out == NULL)
		return (0);
	while (s1[i])
	{
		out[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
		out[i++] = s2[j++];
	out[i] = '\0';
	ft_free_str(&s1);
	return (out);
}
