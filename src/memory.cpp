#include "libunit.h"

static void	*ft_memset(void *s, int c, size_t n)
{
	char	*str;

	str = (char *)s;
	while (n--)
		*str++ = c;
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	tsize;
	size_t	maxsqrt;

	if ((SIZE_MAX / 641u / 6700417u) >= 4294967295u)
		maxsqrt = 65535;
	else
		maxsqrt = 4294967295;
	if (((nmemb > maxsqrt) || (size > maxsqrt))
		&& ((SIZE_MAX / nmemb) < size))
		return (NULL);
	tsize = nmemb * size;
	ptr = malloc(tsize);
	if (!ptr)
		return (ptr);
	ft_memset(ptr, 0, tsize);
	return (ptr);
}

static void	clean_test_unit(t_unit *unit_list)
{
	t_unit	*unit;

	unit = unit_list;
	while (unit != NULL)
	{
		unit_list = unit->next;
		free(unit);
		unit = unit_list;
	}
}

static void	clean_test_suite(t_suite *suite_list)
{
	t_suite	*suite;

	suite = suite_list;
	while (suite != NULL)
	{
		suite_list = suite_list->next;
		clean_test_unit(suite->unit);
		free(suite);
		suite = suite_list;
	}
}

void	clean_exit(int32_t return_value)
{
	t_suite **suite_list;

	suite_list = get_suite_list();
	clean_test_suite(*suite_list);
	exit(return_value);
}