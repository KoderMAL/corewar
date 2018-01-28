/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 16:34:49 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/23 15:16:03 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "asm.h"
#include "util/cqueue.h"

/*
** initializes an instruction
*/

void	instruction_init(t_instruction *instruction, const t_op *op)
{
	instruction->op = op;
	instruction->len = 0;
	instruction->is_lab = 0;
}

/*
** moves an instruction
*/

void	instruction_move(t_instruction *src, t_instruction *dest)
{
	int				i;

	i = 0;
	dest->op = src->op;
	dest->len = src->len;
	dest->is_lab = src->is_lab;
	while (i < src->len)
	{
		dest->arguments[i] = src->arguments[i];
		i++;
	}
	src->op = NULL;
	src->len = 0;
}

/*
** clean an instruction
*/

void	instruction_clean(t_instruction *instruction)
{
	int	j;

	j = 0;
	while (j < instruction->len)
	{
		argument_clean(&(instruction->arguments[j]));
		j++;
	}
	instruction->len = 0;
}
