#include <stdlib.h>
#include "tests/tests.h"
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
	tests_assert_true(env, q->first->next == q->last, "q->first->next == q->last");
	tests_assert_true(env, q->last->next == NULL, "q->last->next == NULL");
	tests_print(env, "\n");
}

static void	cqueue_delete_test(t_tests_env *env, t_cqueue *q)
{
	tests_print(env, "  Testing cqueue_delete ");
	cqueue_delete(q);
	tests_assert_equal_int(env, q->len, 0, "q->len == 0");
	tests_assert_true(env, q->first == NULL, "q->first == NULL");
	tests_assert_true(env, q->last == NULL, "q->last == NULL");
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

static void	cqueue_join_test(t_tests_env *env, t_cqueue *q)
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

static void	ft_cqueue_cmp_test(t_tests_env *env, t_cqueue *q)
{
	tests_print(env, "  Testing ft_cqueue_cmp ");
	cqueue_delete(q);
	tests_assert_equal_int(env, ft_cqueue_cmp("", q), 0, "ft_cqueue_cmp empty");
	tests_assert_equal_int(env, ft_cqueue_cmp("ab", q), 'a', "ft_cqueue_cmp empty ab");
	cqueue_push(q, 'a');
	cqueue_push(q, 'b');
	cqueue_push(q, 'c');
	cqueue_push(q, 'd');
	tests_assert_equal_int(env, ft_cqueue_cmp("", q), -'a', "ft_cqueue_cmp abcd empty");
	tests_assert_equal_int(env, ft_cqueue_cmp("abcd", q), 0, "ft_cqueue_cmp abcd");
	tests_assert_equal_int(env, ft_cqueue_cmp("abce", q), 1, "ft_cqueue_cmp abcd");
	tests_assert_equal_int(env, ft_cqueue_cmp("abcde", q), 'e', "ft_cqueue_cmp abcde");
	tests_print(env, "\n");
}

static void	ft_cqueue_move_test(t_tests_env *env, t_cqueue *q)
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
