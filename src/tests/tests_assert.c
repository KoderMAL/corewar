/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_assert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 11:46:41 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/17 11:37:01 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft/ft.h"
#include "io/openfile.h"
#include "tests.h"

void	tests_assert_ok(t_tests_env *env)
{
	openfile_write_char(&(env->stdout), '.');
}

void	tests_assert_failed(t_tests_env *env, char *err_msg)
{
	openfile_write_char(&(env->stdout), 'F');
	if (err_msg != NULL && err_msg[0] != '\0')
	{
		openfile_write_str(&(env->stderr),
							"Unit test failed with the following error: ",
							0);
		openfile_write_str(&(env->stderr), err_msg, 1);
	}
	openfile_write_char(&(env->stderr), '\n');
	tests_exit(env, 1);
}

void	tests_assert_true(t_tests_env *env, int true, char *err_msg)
{
	if (true)
		tests_assert_ok(env);
	else
		tests_assert_failed(env, err_msg);
}

void	tests_assert_equal_int(t_tests_env *env, int a, int b, char *err_msg)
{
	if (a == b)
		tests_assert_ok(env);
	else
	{
		openfile_write_str(&env->stderr,
							"The following integers whould be equal: ", 0);
		openfile_write_nbr(&env->stderr, a, 0);
		openfile_write_str(&env->stderr, " and ", 0);
		openfile_write_nbr(&env->stderr, b, 1);
		tests_assert_failed(env, err_msg);
	}
}

void	tests_assert_equal_str(t_tests_env *env, char *a, char *b,
								char *err_msg)
{
	if (ft_strcmp(a, b) == 0)
		tests_assert_ok(env);
	else
	{
		openfile_write_str(&env->stderr,
							"The following strings whould be equal: \"", 0);
		openfile_write_str(&env->stderr, a, 0);
		openfile_write_str(&env->stderr, "\" and \"", 0);
		openfile_write_str(&env->stderr, b, 0);
		openfile_write_str(&env->stderr, "\"", 1);
		tests_assert_failed(env, err_msg);
	}
}
