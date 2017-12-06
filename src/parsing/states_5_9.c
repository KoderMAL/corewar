/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_5-9.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 16:50:12 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/06 13:12:35 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "main/asm.h"
#include "parsing.h"

void		state_5(t_env *env, char c)
{
	if (c == ' ' || c == '\t')
	{
		env->col++;
		return ;
	}
	if (c == '"')
		env->state = &state_6;
	env->col++;
}

void		state_6(t_env *env, char c)
{
	if (c == '"')
		env->state = &state_7;
	if (env->name_length == PROG_NAME_LENGTH - 1)
	{
		env->err = 1;
		env->err_msg = "program name too long!\n";
	}
	else
		env->name[env->name_length++] = c;
	env->col++;
}

void		state_7(t_env *env, char c)
{
	if (c == ' ' || c == '\t')
		return ;
	if (c == '\n')
	{
		env->col = 0;
		env->line++;
		env->state = &state_8;
	}
}

void		state_8(t_env *env, char c)
{
	if (c == '\n' || c == ' ' || c == '\t')
		return ;
	else if (c == '.')
		env->state = &state_9;
	else
	{
		env->err = 1;
		env->err_msg = "syntax error at state 8 (comment format)\n";
	}
	env->col++;
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
	env->col++;
}
