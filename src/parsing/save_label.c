#include "main/asm.h"
#include "states.h"

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
