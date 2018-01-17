/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cqueue_test.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 13:48:42 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/17 13:55:48 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CQUEUE_TEST_H
# define CQUEUE_TEST_H
# include "cqueue.h"

/*
** cqueue_test_2.c
*/

void	cqueue_delete_test(t_tests_env *env, t_cqueue *q);
void	cqueue_join_test(t_tests_env *env, t_cqueue *q);
void	ft_cqueue_cmp_test(t_tests_env *env, t_cqueue *q);
void	ft_cqueue_move_test(t_tests_env *env, t_cqueue *q);
void	ft_cqueue_move_test(t_tests_env *env, t_cqueue *q);

/*
** cqueue_test.c
*/

void	cqueue_test(t_tests_env *env);

#endif
