#include "libft.h"

void	ft_free_str_array(char ***arr)
{
	int	i;

	i = 0;
	while (*arr && (*arr)[i])
	{
		ft_free_str(&(*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}
