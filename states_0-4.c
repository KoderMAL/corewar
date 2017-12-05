/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_0-4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 16:33:13 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/05 18:16:28 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdio.h>
void 		state_0(t_env *env, char c)
{
	if (c == '\n' || c == ' ' || c == '\t')
		env->state = &state_0;
	else if (c == '.')
		env->state = &state_1;
	else
	{
		env->err = 1;
		env->err_msg = "syntax error at state 0\n";
	}
	env->col++;
}

void		state_1(t_env *env, char c)
{
	if (c == 'n')
		env->state = &state_2;
	else
	{
		env->err = 1;
		env->err_msg = "syntax error at state 1 (name format)\n";
	}
	env->col++;
}

void		state_2(t_env *env, char c)
{
	if (c == 'a')
	{
		env->state = &state_3;
		env->name_length++;
	}
	else
	{
		env->err = 1;
		env->err_msg = "syntax error at state 2 (name format)\n";
	}
	env->col++;
}

void		state_3(t_env *env, char c)
{
	if (c == 'm')
	{
		env->state = &state_4;
		env->name_length++;
	}
	else
	{
		env->err = 1;
		env->err_msg = "syntax error at state 3 (name format)\n";
	}
	env->col++;
}

void		state_4(t_env *env, char c)
{
	if (c == 'e')
	{
		env->state = &state_5;
		env->name_length++;
	}
	else
	{
		env->err = 1;
		env->err_msg = "syntax error at state 4 (name format)\n";
	}
	env->col++;
}
