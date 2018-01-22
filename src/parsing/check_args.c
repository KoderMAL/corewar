/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 17:32:19 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/22 18:55:24 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main/asm.h"
#include <stdlib.h>

/*
** Fonction de verification de conformite des arguments,
** prend un t_argument.
** Appelle err() si il y a une anomalie.
*/

void			check_value(t_env *env, char *name)
{
	int			i;

	i = 1;
	if (name[i] == '-')
		i++;
	while (name[i])
	{
		if (!ft_isdigit(name[i]) || i > 11)
			err(env, "syntax error while parsing argument", i);
		i++;
	}
}

int				find_labels(t_env *env)
{
	t_argument		*arg;
	t_pqueue_elem	*inst;
	t_instruction	*tmp;
	int				i;
	int				j;

	i = 0;
	inst = env->instructions.first;
	while (i++ < env->instructions.len)
	{
		j = 0;
		tmp = inst->p;
		if (tmp->is_lab == 0)
			while (j < tmp->len)
			{
				arg = &(tmp->arguments[j++]);
				if (arg->type == T_LAB)
				{
					if (!find_label(arg, &env->labels))
						return (0);
				}
			}
		inst = inst->next;
	}
	return (1);
}

int				find_label(t_argument *arg, t_pqueue *labels)
{
	t_pqueue_elem	*tmp;
	t_label			*lab;
	int				i;

	i = 0;
	tmp = labels->first;
	while (i++ < labels->len)
	{
		lab = (t_label*)(tmp->p);
		if (ft_strcmp(arg->name + 2, lab->name) == 0)
		{
			arg->label = tmp->p;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void			check_argument(t_argument *arg, t_env *env)
{
	if (arg->type == T_LAB && (arg->lab_type == T_DIR || arg->lab_type == T_IND))
	{
	}
	else if (arg->type == T_REG)
	{
		if (arg->value > 99 || arg->value < 0)
			err(env, "reg value overflow", 0);
	}
	else if (arg->type == T_IND)
		check_value(env, arg->name);
	else if (arg->type == T_DIR)
		check_value(env, arg->name + 1);
	else
		err(env, "error while checking argument type", 0);
}
