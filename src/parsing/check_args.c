/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 17:32:19 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/10 16:13:05 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 16:39:48 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/09 17:31:51 by alalaoui         ###   ########.fr       */
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
			err(env, "syntax error while parsing argument\n", 0);
		i++;
	}
}

int				find_labels(t_env *env)
{
	t_pqueue_elem	*arg;
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
		arg = tmp->arguments.first;
		while (j++ < tmp->arguments.len)
		{
			if (!find_label(arg->p, &env->labels))
				return (0) ;
			arg = arg->next;
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
		lab = (t_label*)tmp->p;
		printf("arg->name:%s\nlabel->name:%s\n", arg->name, lab->name);
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
	if (arg->type == T_DIR && arg->name[0] == '%' && arg->name[1] == ':')
	{
		if (env->labels.first == NULL)
			err(env, "no labels found\n", 0);
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
//	free(arg->name);
}
