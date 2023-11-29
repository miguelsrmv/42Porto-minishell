#include "libft.h"

void	ft_free_str(char **str)
{
	free(*str);
	*str = NULL;
}
