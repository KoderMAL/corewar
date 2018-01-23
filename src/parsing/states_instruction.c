/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_instruction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 15:46:07 by alalaoui          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2018/01/23 15:42:08 by stoupin          ###   ########.fr       */
=======
/*   Updated: 2018/01/23 15:02:42 by alalaoui         ###   ########.fr       */
>>>>>>> cf4207e10fa9674b6a5d04521b81b7e16405fa19
/*                                                                            */
/* ************************************************************************** */

#include "main/asm.h"
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

void		state_pre_arg(t_env *env, char c)
{
	cqueue_delete(&(env->characters));
<<<<<<< HEAD
	if (c == '\n' || c == COMMENT_CHAR)
=======
	instruction_init(env);
	if (c == '\n' || c == COMMENT_CHAR || c == ';')
>>>>>>> cf4207e10fa9674b6a5d04521b81b7e16405fa19
	{
		save_argument(env);
		save_instruction(env);
		env->state = c == '\n' ? &state_start : &state_comment;
	}
	else if (c == ' ' || c == '\t')
		return ;
	else
	{
		cqueue_push(&(env->characters), c);
		env->state = &state_arg;
	}
}

void		state_arg(t_env *env, char c)
{
	if (c == ' ' || c == '\t')
		env->state = &state_post_arg;
	else if (c == SEPARATOR_CHAR)
	{
		save_argument(env);
		env->state = &state_pre_arg;
	}
	else if (c == COMMENT_CHAR || c == '\n' || c == ';')
	{
		save_argument(env);
		save_instruction(env);
		env->state = c == '\n' ? &state_start : &state_comment;
	}
	else
		cqueue_push(&(env->characters), c);
}

void		state_post_arg(t_env *env, char c)
{
	if (c == ' ' || c == '\t')
		return ;
	else if (c == SEPARATOR_CHAR)
	{
		save_argument(env);
		env->state = &state_pre_arg;
	}
	else if (c == COMMENT_CHAR || c == '\n' || c == ';')
	{
		save_argument(env);
		save_instruction(env);
		env->state = c == '\n' ? &state_start : &state_comment;
	}
}
