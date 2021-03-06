/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_argument.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 15:46:03 by alalaoui          #+#    #+#             */
/*   Updated: 2018/03/06 19:09:35 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include "asm/asm.h"

static void	arg_save(t_argument *arg, int type)
{
	char			*tmp;
	long long		value;

	arg->type = type;
	if (type == T_LAB && arg->name[0] == DIRECT_CHAR &&
			arg->name[1] == LABEL_CHAR)
		arg->lab_type = T_DIR;
	else if (type == T_LAB && arg->name[0] == ':')
		arg->lab_type = T_IND;
	else
	{
		tmp = arg->name;
		if (type == T_DIR || type == T_REG)
			tmp++;
		value = ft_atoi(tmp);
		arg->value = (int)value;
	}
}

static int	check_ind(t_argument *argument)
{
	int				i;

	i = 0;
	if (argument->name[0] == '-')
		i++;
	while (argument->name[i])
	{
		if (!ft_isdigit(argument->name[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	init_arg(t_env *env, t_argument *arg)
{
	if ((arg_from_cqueue(&(env->characters), arg)) == 1)
	{
		err(env, "memory error", -1);
		return ;
	}
	if (arg->name[0] == 'r')
		arg_save(arg, T_REG);
	else if (arg->name[0] == DIRECT_CHAR &&
			arg->name[1] == LABEL_CHAR)
		arg_save(arg, T_LAB);
	else if (arg->name[0] == DIRECT_CHAR)
		arg_save(arg, T_DIR);
	else if (arg->name[0] == LABEL_CHAR && !check_ind(arg))
		arg_save(arg, T_LAB);
	else if (arg->name[0] == LABEL_CHAR || check_ind(arg))
		arg_save(arg, T_IND);
	else
		err(env, "error while parsing arg", env->characters.len);
	arg->line = env->line;
	arg->col = env->col - ft_strlen(arg->name);
}

/*
** Cette fonction doit parser la chaine contenue dans
** env->characters et en remplir arg.
** Ensuite, si tout est correct, arg doit etre
** ajoute a env->instruction.arguments
*/

void		save_argument(t_env *env)
{
	t_argument arg;

	init_arg(env, &arg);
	if (env->err == 0)
		check_argument(&arg, env);
	if (env->err == 0 && env->instruction.len >= env->instruction.op->n_arg)
		err(env, "Too many arguments!", ft_strlen(arg.name) - 1);
	if (env->err == 0)
		env->instruction.arguments[env->instruction.len++] = arg;
	if (env->err != 0 && arg.name)
		free(arg.name);
}
