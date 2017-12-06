/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_15-19.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 11:26:45 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/06 13:43:38 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "main/asm.h"
#include "parsing.h"

void		state_15(t_env *env, char c)
{
	if (c == 't')
		env->state = &state_16;
	else
	{
		env->err = 1;
		env->err_msg = "syntax error at state 15 (comment format)\n";
	}
}

void		state_16(t_env *env, char c)
{
	if (c == ' ' || c == '\t')
		return ;
	if (c == '"')
		env->state = &state_17;
}

void		state_17(t_env *env, char c)
{
	if (c == '"')
		env->state = &state_18;
	if (env->comment_length == COMMENT_LENGTH - 1)
	{
		env->err = 1;
		env->err_msg = "program comment too long!\n";
	}
	else
		env->comment[env->comment_length++] = c;
}

void		state_18(t_env *env, char c)
{
	if (c == ' ' || c == '\t')
		return ;
	if (c == '\n')
		env->state = &state_19;
}

void		state_19(t_env *env, char c)
{
	if (c == '\n')
		return ;
	else if (c == ' ' || c == '\t' || c == '\v')
		return ;
	if (ft_isprint(c))
		env->state = NULL;
}
