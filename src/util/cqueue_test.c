/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cqueue_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 13:49:20 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/17 13:55:00 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tests/tests.h"
#include "cqueue_test.h"
#include "cqueue.h"

static void	cqueue_init_test(t_tests_env *env, t_cqueue *q)
{
	tests_print(env, "  Testing cqueue_init ");
	cqueue_init(q);
	tests_assert_equal_int(env, q->len, 0, "q->len == 0");
	tests_assert_true(env, q->first == NULL, "q->first == NULL");
	tests_assert_true(env, q->last == NULL, "q->last == NULL");
	tests_print(env, "\n");
}

static void	cqueue_push_test(t_tests_env *env, t_cqueue *q, char c1, char c2)
{
	tests_print(env, "  Testing cqueue_push ");
	cqueue_delete(q);
	cqueue_push(q, c1);
	tests_assert_equal_int(env, q->len, 1, "q->len == 1");
	tests_assert_true(env, q->first->c == c1, "q->first->c == c1");
	tests_assert_true(env, q->last->c == c1, "q->last->c == c1");
	tests_assert_true(env, q->first->next == NULL, "q->first->next == NULL");
	cqueue_push(q, c2);
	tests_assert_equal_int(env, q->len, 2, "q->len == 2");
	tests_assert_true(env, q->first->c == c1, "q->first->c == c1");
	tests_assert_true(env, q->last->c == c2, "q->last->c == c2");
	tests_assert_true(env, q->first->next == q->last,
						"q->first->next == q->last");
	tests_assert_true(env, q->last->next == NULL, "q->last->next == NULL");
	tests_print(env, "\n");
}

static void	cqueue_pop_test(t_tests_env *env, t_cqueue *q, char c1, char c2)
{
	tests_print(env, "  Testing cqueue_pop ");
	cqueue_delete(q);
	cqueue_push(q, c1);
	cqueue_push(q, c2);
	tests_assert_true(env, cqueue_pop(q) == c1, "cqueue_pop c1");
	tests_assert_equal_int(env, q->len, 1, "q->len == 1");
	tests_assert_true(env, cqueue_pop(q) == c2, "cqueue_pop c2");
	tests_assert_equal_int(env, q->len, 0, "q->len == 0");
	tests_assert_true(env, cqueue_pop(q) == 0, "cqueue_pop 0");
	tests_print(env, "\n");
}

void		cqueue_test(t_tests_env *env)
{
	t_cqueue	q;
	char		c1;
	char		c2;

	c1 = 'a';
	c2 = 'b';
	tests_print(env, "Testing cqueue\n");
	cqueue_init_test(env, &q);
	cqueue_push_test(env, &q, c1, c2);
	cqueue_delete_test(env, &q);
	cqueue_pop_test(env, &q, c1, c2);
	cqueue_join_test(env, &q);
	ft_cqueue_cmp_test(env, &q);
	ft_cqueue_move_test(env, &q);
}
