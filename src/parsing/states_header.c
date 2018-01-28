/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_header.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 16:29:05 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/28 20:03:50 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm/asm.h"
#include "states.h"

int		match_name(t_env *env)
{
	if (ft_cqueue_cmp(g_name_cmd, &(env->characters)) == 0)
	{
		env->name_check = 1;
		return (1);
	}
	else
		return (0);
}

int		match_comment(t_env *env)
{
	if (ft_cqueue_cmp(g_comment_cmd, &(env->characters)) == 0)
	{
		env->comment_check = 1;
		return (1);
	}
	else
		return (0);
}

void	state_pre_str(t_env *env, char c)
{
	if (c == ' ' || c == '\t')
		return ;
	else if (c == '"')
		env->state = &state_str;
	else
		err(env, "syntax error between parameter and value", 0);
}

void	state_str(t_env *env, char c)
{
	if (c == '"')
	{
		env->state = &state_eol;
		return ;
	}
	if (match_name(env))
	{
		if (env->pos == PROG_NAME_LENGTH)
			err(env, "name too long", 0);
		else
			env->name[env->pos++] = c;
	}
	if (match_comment(env))
	{
		if (env->pos == COMMENT_LENGTH)
			err(env, "comment too long", 0);
		else
			env->comment[env->pos++] = c;
	}
}

void	state_eol(t_env *env, char c)
{
	if (match_name(env))
		env->name[env->pos] = '\0';
	if (match_comment(env))
		env->comment[env->pos] = '\0';
	if (c == ' ' || c == '\t')
		return ;
	else if (c == COMMENT_CHAR || c == ';')
		env->state = &state_comment;
	else if (c == '\n')
		env->state = &state_start;
	else
		err(env, "syntax error at end of line", 0);
}
