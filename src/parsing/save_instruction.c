/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_instruction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 17:48:23 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/05 19:24:35 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main/asm.h"

/*
** Cette fonction doit prendre env->instruction,
** controler que l'instruction est correcte
** puis l'ajouter a env->instructions a l'aide de 
** instruction_dup
*/
#include <stdio.h>
static int		check_types(t_instruction *instruction)
{
	int				i;
	t_pqueue_elem	*arg;
	t_argument		*a;

	arg = instruction->arguments.first;
	i = 0;
	while (instruction->op->arg_type[i])
	{
		a = (t_argument*)arg->p;
		if ((a->type | instruction->op->arg_type[i])
				!= instruction->op->arg_type[i])
			return (-1);
		arg = arg->next;
		i++;
	}
	return (1);
}

static int		check_instruction(t_instruction *instruction)
{
	printf("CHECK%d\nCHECK%d\n", instruction->op->n_arg, instruction->arguments.len) ;
	if (instruction->op->n_arg != instruction->arguments.len)
		return (-1);
	printf("CHECK%d\nCHECK%d\n", instruction->op->n_arg, instruction->arguments.len) ;
	if (check_types(instruction) == -1)
		return (-1);
	return (1);	
}

void			save_instruction(t_env *env)
{
	t_instruction *new;

	new = NULL;
	if (check_instruction(&env->instruction) == -1)
		err(env, "invalid instruction format\n", 0);
	else
	{
		new = instruction_dup(&env->instruction);
		pqueue_push(&env->instructions, new);
	}
}
