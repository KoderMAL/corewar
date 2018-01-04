/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 16:39:48 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/04 17:45:13 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main/asm.h"
#include <stdlib.h>

/*
** Fonction de verification de conformite des arguments,
** prend un t_argument.
** Appelle err() si il y a une anomalie.
*/

static void		check_value(t_env *env, char *name)
{
	int			i;

	i = 1;
	if (name[i] == '-')
		i++;
	while (name[i])
	{
		if (!ft_isdigit(name[i]) || i > 11)
			err(env, "syntax error while parsing argument\n", 0);
		i++;
	}
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
		lab = (t_label*)tmp->p;
		if (ft_strcmp(arg->name, lab->name) == 0)
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
	if (arg->type == T_LAB)
	{
		if (env->labels.first == NULL)
			err(env, "no label found", 0);
		if (!find_label(arg, &env->labels))
			write(1, "NOT FOUND LABEL(recheck_argument)\n", 30); //a supprimer plus tard
	}
	else if (arg->type == T_REG)
	{
		if (arg->value > 99 || arg->value < 0)
			err(env, "reg value overflow\n", 0);
	}
	else if (arg->type == T_IND)
		check_value(env, arg->name);
	else if (arg->type == T_DIR)
		check_value(env, arg->name + 1);
	else
		err(env, "error while checking argument type\n", 0);
	free(arg->name);
}
