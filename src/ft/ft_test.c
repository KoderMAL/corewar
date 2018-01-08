#include "tests/tests.h"
#include "ft_test.h"

void	ft_test(t_tests_env *env)
{
	tests_print(env, "\nTesting ft\n");
	ft_atoi_test(env);
	ft_strchr_test(env);
}
