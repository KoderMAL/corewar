/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_20-24.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 11:26:45 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/08 19:10:26 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main/asm.h"
#include "parsing.h"

void		state_20(t_env *env, char c)
{
	if (c == ':')
	{	
		record_label(env);
		env->state = &state_21;
	}
	else if (ft_strchr(LABEL_CHARS, c) != NULL)
	{
		if (clist_push_front(&(env->clist), c))
		{
			env->err = 1;
			env->err_msg = "memory error while parsing number\n";
		}
		env->offset++;
	}
	else if (c == ' ' || c == '\t')
	{
		if ((env->op = find_name(env)) == NULL)
		{
			env->err = 1;
			env->err_msg = "command not found\n";
		}
		env->state = &state_21;
	}
	else
	{
		env->err = 1;
		env->err_msg("syntax error at state 20");
	}
}

void		state_21(t_env *env, char c)
{
	if (c == ' ' || c == '\t')
		return ;
	else if (c == '#')
	{
		env->state_next = &state_19;
		env->state = &state_comment;
	}
	else if (c == '\n')
		env->state = &state_20;
	// verifier arguments;
}
