/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_instruction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 17:48:23 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/15 16:07:31 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main/asm.h"
#include <stdlib.h>
/*
** Cette fonction doit prendre env->instruction,
** controler que l'instruction est correcte
** puis l'ajouter a env->instructions a l'aide de
** instruction_dup
*/

static int		check_types(t_instruction *instruction)
{
	int				i;
	int				j;
	t_argument		*arg;
	int				lab_type;

	i = 0;
	j = 0;
	lab_type = 0;
	while (instruction->op->arg_type[i])
	{
		arg = instruction->arguments[j];
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
		j++;
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

void			save_instruction(t_env *env)
{
	t_instruction 	*new;
	int				i;

	i = 0;
	new = NULL;
	if (check_instruction(&env->instruction) == -1)
		err(env, "invalid instruction format", 0);
	else
	{
		new = instruction_dup(&env->instruction);
		pqueue_push(&env->instructions, new);
		while (i < env->instruction.len)
		{
			free(env->instruction.arguments[i]);
			i++;
		}
	}
}
