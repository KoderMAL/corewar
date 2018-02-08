/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 11:13:07 by stoupin           #+#    #+#             */
/*   Updated: 2018/02/08 11:14:58 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "parsing/states.h"

static int	parse_char(t_env *env, char c)
{
	(env->state)(env, c);
	if (env->err == 1)
		return (env->err);
	if (c == '\t')
		env->col += 4 - (env->col % 4);
	else if (c == '\n')
	{
		env->col = 0;
		env->line++;
	}
	else
		env->col++;
	return (0);
}

void		parse_input(t_env *env)
{
	char	c;
	int		ret;

	while (env->err == 0)
	{
		ret = openfile_read_char(&(env->input), &c);
		if (ret == -1)
			err(env, "unable to read input", 1);
		if (ret != 1)
			break ;
		parse_char(env, c);
	}
	if (env->err == 0 && env->instructions.len == 0)
		err(env, "no instruction!", 0);
	if (env->err == 0)
		check_labels(env);
	if (env->err == 0 && (!env->name_check || !env->comment_check))
		err(env, "name or comment not found", -1);
}
