/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 16:39:48 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/03 18:00:58 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main/asm.h"

/*
** Fonction de verification de conformite des arguments,
** prend un t_argument.
** Appelle err() si il y a une anomalie.
*/

static void		check_value(t_env *env, char *name)
{
	int			i;

	i = 0;
	if (name[i] == '-')
		i++;
	while (name[i])
	{
		if (!ft_isdigit(name[i]) || i > 11)
			err(env, "syntax error while parsing argument\n");
		i++;
	}
}

void			check_label(t_env *env, t_argument *arg, t_pqueue_elem *tmp)
{
	while (tmp)
	{
		if (ft_strcmp(arg->name, tmp->name) != NULL)
		{
			arg->label = tmp;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void			check_argument(t_argument *arg, t_env *env)
{
	t_pqueue_elem	*tmp;

	if (arg->type = T_LAB)
	{
		if ((tmp = labels->first) == NULL)
			env->err(env, "label not found");
		if (!check_label(env, arg, tmp))
			write(1, "NOT FOUND LABEL(recheck_argument)\n", 30); //a supprimer plus tard
	}
	else if (arg_type == T_REG)
		if (arg->value > 99 || arg->value < 0)
			env->err(env, "reg value overflow\n");
	else if (arg_type == T_IND)
		check_value(env, arg->name);
	else if (arg_type == T_DIR)
		check_value(env, arg-name + 1);
	else
		err(env, "error while checking argument type\n");
	free(arg->name);
}
