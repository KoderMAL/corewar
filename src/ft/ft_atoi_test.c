/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 11:27:13 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/17 11:27:44 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/tests.h"
#include "ft.h"

void	ft_atoi_test(t_tests_env *env)
{
	tests_print(env, "  Testing ft_atoi ");
	tests_assert_equal_int(env, ft_atoi("42"), 42, "ft_atoi failed with 42");
	tests_assert_equal_int(env, ft_atoi("-42"), -42, "ft_atoi failed with -42");
	tests_assert_equal_int(env, ft_atoi("0"), 0, "ft_atoi failed with 0");
	tests_assert_equal_int(env, ft_atoi("2147483647"), 2147483647,
							"ft_atoi failed with INT_MAX");
	tests_assert_equal_int(env, ft_atoi("-2147483648"), -2147483648,
							"ft_atoi failed with INT_MIN");
	tests_print(env, "\n");
}
