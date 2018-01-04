/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_instruction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 15:46:07 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/04 14:07:49 by alalaoui         ###   ########.fr       */
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

void	state_pre_arg(t_env *env, char c)
{
	cqueue_delete(&(env->characters));
	instruction_init(env);
	if (c == '\n' || c == COMMENT_CHAR)
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

void	state_arg(t_env *env, char c)
{
	if (c == ' ' || c == '\t')
		env->state = &state_post_arg;
	else if (c == SEPARATOR_CHAR)
	{
		save_argument(env);
		env->state = &state_pre_arg;
	}
	else if (c == COMMENT_CHAR || c == '\n')
	{
		save_argument(env);
		save_instruction(env);
		env->state = c == '\n' ? &state_start : &state_comment;
	}
	else
		cqueue_push(&(env->characters), c);
}

void	state_post_arg(t_env *env, char c)
{
	if (c == ' ' || c == '\t')
		return ;
	else if (c == SEPARATOR_CHAR)
	{
		save_argument(env);
		env->state = &state_pre_arg;
	}
	else if (c == COMMENT_CHAR || c == '\n')
	{
		save_argument(env);
		save_instruction(env);
		env->state = c == '\n' ? &state_start : &state_comment;
	}
}
