# include "libunit.h"

static int32_t	test_assert(bool condition, const char *message, va_list *ap)
{
	int32_t result;

	result = EXIT_FAILURE;
	if (condition == true)
		result = EXIT_SUCCESS;
	else
		vfprintf(stderr, message, *ap);
	va_end(*ap);
	return (result);
}

int32_t	assert_equal_int(int32_t expected, int32_t actual, const char *message, ...)
{
	va_list ap;

	va_start(ap, message);
	return (test_assert((actual == expected), message, &ap));
}

int32_t	assert_not_equal_int(int32_t threshold, int32_t actual, const char *message, ...)
{
	va_list ap;

	va_start(ap, message);
	return (test_assert((actual != threshold), message, &ap));
}

int32_t	assert_null(void *pointer, const char *message, ...)
{
	va_list ap;

	va_start(ap, message);
	return (test_assert((pointer == NULL), message, &ap));
}

int32_t	assert_not_null(void *pointer, const char *message, ...)
{
	va_list ap;

	va_start(ap, message);
	return (test_assert((pointer != NULL), message, &ap));
}