#include <stdlib.h>
#include "tests/tests.h"
#include "pqueue.h"

static void	pqueue_init_test(t_tests_env *env, t_pqueue *q)
{
	tests_print(env, "  Testing pqueue_init ");
	pqueue_init(q);
	tests_assert_equal_int(env, q->len, 0, "q->len == 0");
	tests_assert_true(env, q->first == NULL, "q->first == NULL");
	tests_assert_true(env, q->last == NULL, "q->last == NULL");
	tests_print(env, "\n");
}

static void	pqueue_push_test(t_tests_env *env, t_pqueue *q, void *s1, void *s2)
{
	tests_print(env, "  Testing pqueue_push ");
	pqueue_push(q, s1);
	tests_assert_equal_int(env, q->len, 1, "q->len == 1");
	tests_assert_true(env, q->first->p == s1, "q->first->p == s1");
	tests_assert_true(env, q->last->p == s1, "q->last->p == s1");
	tests_assert_true(env, q->first->next == NULL, "q->first->next == NULL");
	pqueue_push(q, s2);
	tests_assert_equal_int(env, q->len, 2, "q->len == 2");
	tests_assert_true(env, q->first->p == s1, "q->first->p == s1");
	tests_assert_true(env, q->last->p == s2, "q->last->p == s2");
	tests_assert_true(env, q->first->next == q->last, "q->first->next == q->last");
	tests_assert_true(env, q->last->next == NULL, "q->last->next == NULL");
	tests_print(env, "\n");
}

static void	pqueue_delete_test(t_tests_env *env, t_pqueue *q)
{
	tests_print(env, "  Testing pqueue_delete ");
	pqueue_delete(q);
	tests_assert_equal_int(env, q->len, 0, "q->len == 0");
	tests_assert_true(env, q->first == NULL, "q->first == NULL");
	tests_assert_true(env, q->last == NULL, "q->last == NULL");
	tests_print(env, "\n");
}

void		pqueue_test(t_tests_env *env)
{
	void		*s1;
	void		*s2;
	t_pqueue	q;

	s1 = malloc(42);
	s2 = malloc(42);

	tests_print(env, "Testing pqueue\n");
	pqueue_init_test(env, &q);
	pqueue_push_test(env, &q, s1, s2);
	pqueue_delete_test(env, &q);
}
