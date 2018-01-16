/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 16:34:49 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/16 17:29:23 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "asm.h"
#include "util/cqueue.h"

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
		env->instruction.is_lab = 0;
		env->op = NULL;
	}
}

/*
** duplicates an instruction
*/

t_instruction	*instruction_dup(t_instruction *instruction)
{
	t_instruction	*new_instruction;
	int				i;

	i = 0;
	new_instruction = (t_instruction*)malloc(sizeof(t_instruction));
	if (new_instruction == NULL)
		return (NULL);
	new_instruction->op = instruction->op;
	new_instruction->len = instruction->len;
	new_instruction->is_lab = instruction->is_lab;
	while (i < instruction->len)
	{
		new_instruction->arguments[i] = argument_dup(instruction->arguments[i]);
		i++;
	}
	return (new_instruction);
}
