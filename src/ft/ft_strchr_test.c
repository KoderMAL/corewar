/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 11:27:52 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/17 11:27:53 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
