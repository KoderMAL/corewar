/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_pass.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 17:28:49 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/09 17:00:23 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembly.h"

void	*get_op(t_instruction *instruction)
{
	if (instruction->op.opcode == 1)
		return (&assemble_live);
	else if (instruction->op.opcode == 2)
		return (&assemble_ld);
	else if (instruction->op.opcode == 3)
		return (&assemble_st);
	else if (instruction->op.opcode == 4)
		return (&assemble_add);
	else if (instruction->op.opcode == 5)
		return (&assemble_sub);
	else if (instruction->op.opcode == 6)
		return (&assemble_and);
	else if (instruction->op.opcode == 7)
		return (&assemble_or);
	else if (instruction->op.opcode == 8)
		return (&assemble_xor);
	else if (instruction->op.opcode == 9)
		return (&assemble_zjump);
	else if (instruction->op.opcode == 10)
		return (&assemble_ldi);
	else if (instruction->op.opcode == 11)
		return (&assemble_sti);
	else if (instruction->op.opcode == 12)
		return (&assemble_fork);
	else if (instruction->op.opcode == 13)
		return (&assemble_lld);
	else if (instruction->op.opcode == 14)
		return (&assemble_lldi);
	else if (instruction->op.opcode == 15)
		return (&assemble_lfork);
	else if (instruction->op.opcode == 16)
		return (&assemble_aff);
}

void	first_pass(char	*champ, t_pqueue instructions, t_pqueue *gaps)
{
	int	LC;
	int i;
	void (*assemble_op)(char *champ, int *LC, t_pqueue *gaps, t_pqueue args);
	t_pqueue_elem	*elem;

	i = 0;
	LC = 0;
	elem = instructions->first;
	while (i < instructions.len)
	{
		if (elem->p.is_lab == false)
		{
			assemble_op = get_op(elem->p);
			(assemble_op)(champ, &LC, gaps, elem->p.arguments);
		}
		else
			//call store lab function with *LC and the elem->p to store the LC;
			//if elem->p islab (call store_lab_location)
	}



}
