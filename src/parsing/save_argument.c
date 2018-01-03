/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_argument.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 15:46:03 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/03 18:07:24 by alalaoui         ###   ########.fr       */
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
	char			*tmp;

	arg->type = type;
	if (type == T_LAB)
		arg->name = cqueue_join(&(env->characters));
	else
	{
		arg->name = cqueue_join(&(env->characters));
		tmp = arg->name;
		type == T_DIR ?	tmp++ : 0;
		arg->value = ft_atoi(tmp);
	}
}

static void		init_arg(t_env *env)
{
	t_argument	*arg;

	arg = (t_argument*)malloc(sizeof(t_argument));
	arg->type = 0;
	arg->value = 0;
	arg->name = NULL;
	arg->label = NULL;
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
