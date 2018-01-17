/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 11:46:29 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/16 11:46:35 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "tests.h"

void	tests_init(t_tests_env *env)
{
	openfile_init(&(env->stdout), STDOUT_FILENO);
	openfile_init(&(env->stderr), STDERR_FILENO);
}

void	tests_clean(t_tests_env *env)
{
	openfile_flush(&(env->stdout));
	openfile_flush(&(env->stderr));
}

void	tests_exit(t_tests_env *env, int code)
{
	openfile_write_char(&(env->stdout), '\n');
	tests_clean(env);
	exit(code);
}

void	tests_print(t_tests_env *env, char *msg)
{
	openfile_write_str(&(env->stdout), msg, 0);
}
