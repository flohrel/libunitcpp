#include "libunit.h"

t_suite	**get_suite_list(void)
{
	static t_suite *suite_list = NULL;
	return (&suite_list);
}

size_t	ft_strlen(const char *s)
{
	const char	*str;

	str = s;
	if (str)
		while (*str++)
			;
	return (str - s - 1);
}