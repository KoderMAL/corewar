/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_15-19.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 11:26:45 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/13 11:42:21 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "main/asm.h"
#include "parsing.h"

void	state_15(t_env *env, char c)
{
	if (c == 't')
		env->state = &state_16;
	else
		err(env, "syntax error at state 15 (comment format)");
}

void	state_16(t_env *env, char c)
{
	if (c == ' ' || c == '\t')
		return ;
	else if (c == '"')
		env->state = &state_17;
	else
		err(env, "syntax error at state 16 (comment format)");
}

void	state_17(t_env *env, char c)
{
	if (c == '"')
		env->state = &state_18;
	else if (env->comment_length == COMMENT_LENGTH - 1)
		err(env, "program comment too long!");
	else
		env->comment[env->comment_length++] = c;
}

void	state_18(t_env *env, char c)
{
	if (c == ' ' || c == '\t')
		return ;
	else if (c == '\n')
		env->state = &state_19;
	else if (c == '#')
	{
		env->state_next = &state_19;
		env->state = &state_comment;
	}
	else
		err(env, "syntax error at state 18 (comment format)");
}

void	state_19(t_env *env, char c)
{
	if (c == '\n')
		return ;
	else if (c == ' ' || c == '\t' || c == '\v')
		return ;
	else if (c == '#')
	{
		env->state_next = &state_19;
		env->state = &state_comment;
	}
	else if (ft_strchr(LABEL_CHARS, c))
		env->state = &state_20;
	else
		err(env, "syntax error at state 19 (awaiting instruction)");
}
