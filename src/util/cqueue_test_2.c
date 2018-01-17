/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cqueue_test_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 13:54:20 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/17 13:56:03 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cqueue.h"
#include "tests/tests.h"

void	cqueue_delete_test(t_tests_env *env, t_cqueue *q)
{
	tests_print(env, "  Testing cqueue_delete ");
	cqueue_delete(q);
	tests_assert_equal_int(env, q->len, 0, "q->len == 0");
	tests_assert_true(env, q->first == NULL, "q->first == NULL");
	tests_assert_true(env, q->last == NULL, "q->last == NULL");
	tests_print(env, "\n");
}

void	cqueue_join_test(t_tests_env *env, t_cqueue *q)
{
	char *s;

	tests_print(env, "  Testing cqueue_join ");
	cqueue_delete(q);
	s = cqueue_join(q);
	tests_assert_equal_str(env, s, "", "cqueue_join empty");
	free(s);
	cqueue_push(q, 'a');
	cqueue_push(q, 'b');
	cqueue_push(q, 'c');
	cqueue_push(q, 'd');
	s = cqueue_join(q);
	tests_assert_equal_str(env, s, "abcd", "cqueue_join 'abcd'");
	free(s);
	tests_assert_equal_int(env, q->len, 0, "q->len == 0");
	tests_assert_true(env, q->first == NULL, "q->first == NULL");
	tests_assert_true(env, q->last == NULL, "q->last == NULL");
	tests_print(env, "\n");
}

void	ft_cqueue_cmp_test(t_tests_env *env, t_cqueue *q)
{
	tests_print(env, "  Testing ft_cqueue_cmp ");
	cqueue_delete(q);
	tests_assert_equal_int(env, ft_cqueue_cmp("", q), 0,
							"ft_cqueue_cmp empty");
	tests_assert_equal_int(env, ft_cqueue_cmp("ab", q), 'a',
							"ft_cqueue_cmp empty ab");
	cqueue_push(q, 'a');
	cqueue_push(q, 'b');
	cqueue_push(q, 'c');
	cqueue_push(q, 'd');
	tests_assert_equal_int(env, ft_cqueue_cmp("", q), -'a',
							"ft_cqueue_cmp abcd empty");
	tests_assert_equal_int(env, ft_cqueue_cmp("abcd", q), 0,
							"ft_cqueue_cmp abcd");
	tests_assert_equal_int(env, ft_cqueue_cmp("abce", q), 1,
							"ft_cqueue_cmp abcd");
	tests_assert_equal_int(env, ft_cqueue_cmp("abcde", q), 'e',
							"ft_cqueue_cmp abcde");
	tests_print(env, "\n");
}

void	ft_cqueue_move_test(t_tests_env *env, t_cqueue *q)
{
	char	s[42];

	tests_print(env, "  Testing ft_cqueue_move ");
	cqueue_delete(q);
	cqueue_push(q, 'a');
	cqueue_push(q, 'b');
	cqueue_push(q, 'c');
	cqueue_push(q, 'd');
	ft_cqueue_move(s, q);
	tests_assert_equal_str(env, s, "abcd", "ft_cqueue_move abcd");
	cqueue_delete(q);
	ft_cqueue_move(s, q);
	tests_assert_equal_str(env, s, "", "ft_cqueue_move empty");
	tests_print(env, "\n");
}
