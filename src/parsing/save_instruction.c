/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_instruction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 17:48:23 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/17 14:02:58 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main/asm.h"
#include <stdlib.h>

static int		check_types(t_instruction *instruction)
{
	int				i;
	t_argument		*arg;

	i = 0;
	while (instruction->op->arg_type[i])
	{
		arg = &(instruction->arguments[i]);
		if (arg->type == T_LAB)
		{
			if ((arg->lab_type | instruction->op->arg_type[i])
					!= instruction->op->arg_type[i])
				return (-1);
		}
		else
		{
			if ((arg->type | instruction->op->arg_type[i])
					!= instruction->op->arg_type[i])
				return (-1);
		}
		i++;
	}
	return (1);
}

static int		check_instruction(t_instruction *instruction)
{
	if (instruction->op->n_arg != instruction->len)
		return (-1);
	if (check_types(instruction) == -1)
		return (-1);
	return (1);
}

/*
** Cette fonction doit prendre env->instruction,
** controler que l'instruction est correcte
** puis l'ajouter a env->instructions a l'aide de
** instruction_dup
*/

void			save_instruction(t_env *env)
{
	t_instruction	*new;

	new = NULL;
	if (check_instruction(&env->instruction) == -1)
		err(env, "invalid instruction format", 0);
	else
	{
		new = (t_instruction*)malloc(sizeof(t_instruction));
		if (new == NULL)
			err(env, "memory error", -1);
		instruction_move(&env->instruction, new);
		pqueue_push(&env->instructions, new);
	}
}
