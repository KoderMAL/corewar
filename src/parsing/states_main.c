/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 16:33:13 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/28 20:03:44 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm/asm.h"
#include "states.h"

void	state_start(t_env *env, char c)
{
	cqueue_delete(&(env->characters));
	env->pos = 0;
	if (c == '\n' || c == ' ' || c == '\t')
		return ;
	else if (c == COMMENT_CHAR || c == ';')
		env->state = &state_comment;
	else
	{
		cqueue_push(&(env->characters), c);
		env->state = &state_command_label_instruction;
	}
}

void	state_comment(t_env *env, char c)
{
	if (c == '\n')
		env->state = &state_start;
}

void	state_command_label_instruction(t_env *env, char c)
{
	if (c == LABEL_CHAR)
		save_label(env);
	else if (c == '"')
	{
		if (match_name(env) || match_comment(env))
			env->state = &state_str;
		else
			err(env, "illegal command", env->characters.len);
	}
	else if (c == ' ' || c == '\t')
	{
		if (match_name(env) || match_comment(env))
			env->state = &state_pre_str;
		else if ((env->op = match_instruction(env)))
		{
			instruction_init(&env->instruction, env->op);
			env->state = &state_pre_arg;
		}
		else
			err(env, "illegal instruction", env->characters.len);
	}
	else if (c == '\n' || c == '#')
		err(env, "syntax error", 0);
	else
		cqueue_push(&(env->characters), c);
}
