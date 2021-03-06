/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 17:32:19 by alalaoui          #+#    #+#             */
/*   Updated: 2018/02/08 11:40:27 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm/asm.h"

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
		if (!ft_isdigit(name[i]))
		{
			err(env, "syntax error while parsing argument",
					ft_strlen(name) - i);
			break ;
		}
		i++;
	}
}

int				check_labels(t_env *env)
{
	t_argument		*arg;
	t_pqueue_elem	*inst;
	int				i;
	int				j;

	i = 0;
	inst = env->instructions.first;
	while (i++ < env->instructions.len)
	{
		j = 0;
		if (((t_instruction*)inst->p)->is_lab == 0)
			while (j < ((t_instruction*)inst->p)->len)
			{
				arg = &(((t_instruction*)inst->p)->arguments[j++]);
				if (arg->type == T_LAB)
				{
					env->line = arg->line;
					env->col = arg->col;
					if (!find_label(arg, &env->labels))
						return (err(env, "label not found", 0));
				}
			}
		inst = inst->next;
	}
	return (0);
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
		if ((arg->lab_type == T_DIR
				&& ft_strcmp(arg->name + 2, lab->name) == 0)
			|| (arg->lab_type == T_IND
					&& ft_strcmp(arg->name + 1, lab->name) == 0))
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
	env->line = arg->line;
	env->col = arg->col;
	if (arg->type == T_LAB
		&& (arg->lab_type == T_DIR || arg->lab_type == T_IND))
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
