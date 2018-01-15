/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 16:34:49 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/10 16:34:50 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "asm.h"

/*
** initializes an instruction
** instruction->arguments must have been initialized with pqueue_init first!
*/

void			instruction_init(t_env *env)
{
	if (env->op)
	{
		env->instruction.op = env->op;
		env->instruction.len = 0;
		env->op = NULL;
	}
}

/*
** duplicates an instruction
*/

t_instruction	*instruction_dup(t_instruction *instruction)
{
	t_instruction	*new_instruction;

	new_instruction = (t_instruction*)malloc(sizeof(t_instruction));
	if (new_instruction == NULL)
		return (NULL);
	new_instruction->op = instruction->op;
	new_instruction->arguments[0] = instruction->arguments[0];
	new_instruction->arguments[1] = instruction->arguments[1];
	new_instruction->arguments[2] = instruction->arguments[2];
	new_instruction->arguments[3] = instruction->arguments[3];
	return (new_instruction);
}
