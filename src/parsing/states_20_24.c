/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_20-24.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 11:26:45 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/13 17:56:38 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main/asm.h"
#include "parsing.h"

void	state_20(t_env *env, char c)
{
	if (c == ':')
	{	
		record_label(env);
		env->state = &state_21;
	}
	else if (ft_strchr(LABEL_CHARS, c) != NULL)
	{
		if (cqueue_push(&(env->cqueue), c))
			err(env, "memory error while parsing number");
		env->offset++;
	}
	else if (c == ' ' || c == '\t')
	{
		if ((env->op = find_op(env)) == NULL)
			err(env, "command not found");
		env->state = &state_21;
	}
	else
		err(env, "syntax error at state 20");
}

void	state_21(t_env *env, char c)
{
	if (c == ' ' || c == '\t')
		return ;
	else if (c == '#')
	{
		env->state_next = &state_21;
		env->state = &state_comment;
	}
	else if (ft_strchr(LABEL_CHARS, c) != NULL || c == ':' || c == '%' ||
			c == ',')
	{
		if (cqueue_push(&(env->cqueue), c))
			err(env, "memory error while parsing number");
		env->offset++;
	}
	else if (c == '\n')
	{
		parse_arguments(env);
		env->state = &state_20;
	}
	// verifier arguments;
}
