#include <stdlib.h>
#include "tests/tests.h"
#include "ft.h"

void	ft_strchr_test(t_tests_env *env)
{
	char *str;

	str = "abcdef";
	tests_print(env, "  Testing ft_strchr ");
	tests_assert_true(env, ft_strchr(str, 'a') == str, NULL);
	tests_assert_true(env, ft_strchr(str, 'b') == str + 1, NULL);
	tests_assert_true(env, ft_strchr(str, 'g') == NULL, NULL);
	tests_print(env, "\n");
}
