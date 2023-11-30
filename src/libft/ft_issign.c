#include "libft.h"

bool	ft_issign(char c)
{
	if (c == '+' || c == '-')
		return (true);
	return (false);
}
