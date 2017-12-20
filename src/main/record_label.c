/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record_label.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 17:24:02 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/08 19:08:16 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "asm.h"
#include "util/clist.h"

t_label		*init_label(t_env *env)
{
	t_label	*label;

	label = (t_label*)malloc(sizeof(t_label));
	if (!label)
	{
		env->err = 1;
		env->err_msg = "memory error after malloc call\n";
	}
	label->label = NULL;
	label->offset = env->offset;
	label->next = NULL;
	return (label);
}

void		record_label(t_env *env)
{
	t_label	*new;

	new = init_label(env);
	if (!env->labels)
		env->labels = new;
	else
	{
		new->next = env->labels;
		env->labels = new;
	}
	if ((new->label = clist_join(&(env->clist))) == NULL)
	{
		env->err = 1;
		env->err_msg = "memory error while joining label\n";
	}
}

int			ft_clist_cmp(char *name, t_clist *clist)
{
	int				i;
	t_clist_elem	*elem;

	i = 0;
	elem = clist->first;
	while (i < clist->len)
	{
		if (name[i] != elem->c)
			return (name[i] - elem->c);
		i++;
		elem = elem->next;
	}
	return (name[i]);
}

const t_op	*find_op(t_env *env)
{
	const t_op	*op;
	
	op = g_op_tab;
	while (op->name)
	{
		if (ft_clist_cmp(op->name, &env->clist) == 0)
			return (op);
		op++;
	}
	return (NULL);
}

void		record_command();

void		record_arg();
