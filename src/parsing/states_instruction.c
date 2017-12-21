#include "main/asm.h"
#include "main/op.h"
#include "states.h"

const t_op	*match_instruction(t_env *env)
{
	int	i;

	i = 0;
	while (g_op_tab[i].name != 0)
	{
		if (ft_cqueue_cmp(g_op_tab[i].name, &(env->characters)) == 0)
			return (&(g_op_tab[i]));
		i++;
	}
	return (NULL);
}

void	state_pre_arg(t_env *env, char c)
{
	if (c == '\n')
		env->state = &state_start;
}
