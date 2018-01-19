/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 18:39:49 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/19 16:59:19 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembly.h"

void	assemble_op(unsigned char *champ, int *LC, t_pqueue *gaps, t_instruction *instruction)
{
	int		i;
	int		gapLC;

	i = 0;
	gapLC = *LC;
	champ[(*LC)++] = instruction->op->opcode;
	if (instruction->op->has_pcode)
		champ[(*LC)++] = encode_param_byte(instruction);
	while (i < instruction->len)
	{
		if (instruction->arguments[i].type == T_LAB)
			store_gap(LC, gaps, instruction->arguments[i], instruction->op->has_idx, gapLC);
		else if (instruction->arguments[i].type == T_DIR)
		{
			if (instruction->op->has_idx)
				encode_2_bytes(champ, LC, instruction->arguments[i].value);
			else
				encode_4_bytes(champ, LC, instruction->arguments[i].value);
		}
		else if (instruction->arguments[i].type == T_IND)
			encode_2_bytes(champ, LC, instruction->arguments[i].value);
		else if (instruction->arguments[i].type == T_REG)
		{
			encode_1_byte(champ, LC, instruction->arguments[i].value);
		}
			i++;
	}	

}
