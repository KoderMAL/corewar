/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_5-9.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 16:50:12 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/06 13:42:47 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "main/asm.h"
#include "parsing.h"

void		state_5(t_env *env, char c)
{
	if (c == ' ' || c == '\t')
		return ;
	else if (c == '"')
	{
		env->state = &state_6;
		env->name_length = 0;
	}
	else
	{
		env->err = 1;
		env->err_msg = "syntax error at state 5 (name format)\n";
	}
}

void		state_6(t_env *env, char c)
{
	if (c == '"')
		env->state = &state_7;
	else if (env->name_length == PROG_NAME_LENGTH - 1)
	{
		env->err = 1;
		env->err_msg = "program name too long!\n";
	}
	else
		env->name[env->name_length++] = c;
}

void		state_7(t_env *env, char c)
{
	if (c == ' ' || c == '\t')
		return ;
	else if (c == '\n')
		env->state = &state_8;
	else if (c == '#')
	{
		env->state_next = &state_8;
		env->state = &state_comment;
	}
	else
	{
		env->err = 1;
		env->err_msg = "syntax error at state 7 (name format)\n";
	}
}

void		state_8(t_env *env, char c)
{
	if (c == '\n' || c == ' ' || c == '\t')
		return ;
	else if (c == '.')
		env->state = &state_9;
	else if (c == '#')
	{
		env->state_next = &state_8;
		env->state = &state_comment;
	}
	else
	{
		env->err = 1;
		env->err_msg = "syntax error at state 8 (name format)\n";
	}
}

void		state_9(t_env *env, char c)
{
	if (c == 'c')
		env->state = &state_10;
	else
	{
		env->err = 1;
		env->err_msg = "syntax error at state 9 (comment format)\n";
	}
}
