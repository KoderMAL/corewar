#include "main/asm.h"
#include "main/op.h"
#include "states.h"
#include "util/pqueue.h"

int		check_label(t_env *env)
{
	t_cqueue_elem	*elem;
	int				i;

	elem = env->characters.first;
	i = 0;
	while (i < env->characters.len && env->err == 0)
	{
		if (!ft_strchr(g_label_chars, elem->c))
			err(env, "incorrect character in label", i - env->characters.len);
		elem = elem->next;
		i++;
	}
	if (env->err == 0)
		return (1);
	else
		return (0);
}

void	save_label(t_env *env)
{
	int	error;

	if (check_label(env))
	{
		error = pqueue_push(
				&(env->labels),
				label_from_cqueue(&(env->characters), env->instructions.len)
				);
		if (error)
			err(env, "memory error", -1);
	}
	env->header = 0;
	env->state = &state_start;
}
