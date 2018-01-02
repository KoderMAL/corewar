/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_argument.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 15:46:03 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/02 17:22:57 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main/asm.h"

/*
** Cette fonction doit parser la chaine contenue dans
** env->characters et en remplir arg.
** Ensuite, si tout est correct, arg doit etre
** ajoute a env->instruction.arguments a l'aide de
** argument_dup.
*/

static void		arg_save(t_pqueue *pq, t_argument *arg, int type)
{
	int				i;
	t_pqueue_elem	tmp;
	i = 0;
	tmp = pq->first;
	arg->type = type;
	if (type == T_LAB)
	{
		// probablement segfault: a enregistrer autrement.
		arg->value[0] = cqueue_join(&(env->characters));
		arg->value[1] = '\0';
		return ;
	}
	while (i < pq->len)
	{
		arg->value[i++] = tmp->c;
		tmp = tmp->next;
	}
	arg->value[i] = '\0';
}

static void		init_arg(t_env *env)
{
	t_argument	*arg;

	arg = (t_argument*)malloc(sizeof(t_argument));
	if (env->character->first->c = ':')
		arg_save(env->instruction->arguments, arg, T_DIR);
	else if (env->character->first->c = 'r')
		arg_save(env->instruction->arguments, arg, T_REG);
	else if (env->character->first->c = '%' &&
			env->character->first->next->c = ':')
		arg_save(env->instruction->arguments, arg, T_LAB);
	else if (env->character->first = '%')
		arg_save(env->instruction->arguments, arg, T_IND);
	else
		err(env, "error while parsing arg\n");
	return (arg);
}

void	save_argument(t_env *env)
{
	t_argument *arg;
	
	arg = init_arg(env);
	!env->err ? check_argument(arg, env) : 0;
	!env->err ? pqueue_push(&(env->instruction->arguments), arg) :
		pqueue_delete(&(env->instruction->arguments));
}
