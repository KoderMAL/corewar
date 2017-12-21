#include "main/asm.h"
#include "main/op.h"
#include "states.h"

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
	if (check_label(env))
		siqueue_push_cqueue(&(env->labels), &(env->characters), env->instructions.len);
	env->header = 0;
	env->state = &state_start;
}
