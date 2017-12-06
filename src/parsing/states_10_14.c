/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_10-14.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 10:56:20 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/06 13:05:39 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "main/asm.h"
#include "parsing.h"

void			state_10(t_env *env, char c)
{
	if (c == 'o')
		env->state = &state_11;
	else
	{
		env->err = 1;
		env->err_msg = "syntax error at state 10 (comment format)\n";
	}
	env->col++;
}

void			state_11(t_env *env, char c)
{
	if (c == 'm')
		env->state = &state_12;
	else
	{
		env->err = 1;
		env->err_msg = "syntax error at state 11 (comment format)\n";
	}
	env->col++;
}

void			state_12(t_env *env, char c)
{
	if (c == 'm')
		env->state = &state_13;
	else
	{
		env->err = 1;
		env->err_msg = "syntax error at state 12 (comment format)\n";
	}
	env->col++;
}

void			state_13(t_env *env, char c)
{
	if (c == 'e')
		env->state = &state_14;
	else
	{
		env->err = 1;
		env->err_msg = "syntax error at state 13 (comment format)\n";
	}
	env->col++;
}

void			state_14(t_env *env, char c)
{
	if (c == 'n')
		env->state = &state_15;
	else
	{
		env->err = 1;
		env->err_msg = "syntax error at state 14 (comment format)\n";
	}
	env->col++;
}
