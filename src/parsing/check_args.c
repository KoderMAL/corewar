/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 16:39:48 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/03 17:04:57 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main/asm.h"

/*
** Fonction de verification de conformite des arguments,
** prend un t_argument.
** Appelle err() si il y a une anomalie.
*/

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
			write(1, "NOT FOUND LABEL(check_argument)\n", 30);
	}
}
