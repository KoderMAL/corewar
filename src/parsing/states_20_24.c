/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_20-24.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 11:26:45 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/13 11:30:48 by alalaoui         ###   ########.fr       */
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
			ft_err(env, "memory error while parsing number\n");
		env->offset++;
	}
	else if (c == ' ' || c == '\t')
	{
		if ((env->op = find_op(env)) == NULL)
			ft_err(env, "command not found\n");
		env->state = &state_21;
	}
	else
		ft_err(env, "syntax error at state 20");
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
