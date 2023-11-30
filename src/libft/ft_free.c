#include "libft.h"

void	*ft_free(void **p)
{
	if (p == NULL)
		return (NULL);
	free(*p);
	*p = NULL;
	return (NULL);
}
