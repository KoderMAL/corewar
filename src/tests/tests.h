/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 11:46:52 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/17 11:36:38 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include "io/openfile.h"

typedef struct	s_tests_env
{
	t_openfile	stdout;
	t_openfile	stderr;
}				t_tests_env;

/*
** from tests.c
*/

void			tests_init(t_tests_env *env);
void			tests_clean(t_tests_env *env);
void			tests_exit(t_tests_env *env, int code);
void			tests_print(t_tests_env *env, char *msg);

/*
** from tests_assert.c
*/

void			tests_assert_ok(t_tests_env *env);
void			tests_assert_failed(t_tests_env *env, char *err_msg);
void			tests_assert_true(t_tests_env *env, int true, char *err_msg);
void			tests_assert_equal_int(t_tests_env *env, int a, int b,
										char *err_msg);
void			tests_assert_equal_str(t_tests_env *env, char *a, char *b,
										char *err_msg);

#endif
