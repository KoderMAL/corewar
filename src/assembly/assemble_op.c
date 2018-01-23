/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 18:39:49 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/23 13:48:06 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "util/pqueue.h"
#include "assembly.h"

void	assemble_op_fake(int *LC, t_pqueue *gaps, t_instruction *instruction)
{
	int		i;
	int		gapLC;

	i = 0;
	gapLC = *LC;
	(*LC)++;
	if (instruction->op->has_pcode)
		(*LC)++;
	while (i < instruction->len)
	{
		if (instruction->arguments[i].type == T_LAB)
			store_gap(LC, gaps, instruction->arguments[i], instruction->op->has_idx, gapLC);
		else if (instruction->arguments[i].type == T_DIR)
		{
			if (instruction->op->has_idx)
				(*LC) += 2;
			else
				(*LC) += 4;
		}
		else if (instruction->arguments[i].type == T_IND)
			(*LC) += 2;
		else if (instruction->arguments[i].type == T_REG)
			(*LC)++;
		i++;
	}	
}

void	fill_gap(unsigned char *champion, int *LC, t_gap *gap)
{
	int				value;

		// check that *LC == gap->location
		if (*LC != gap->location)
		{
			printf("ERROR: LC = %d, gap->location = %d\n", *LC, gap->location);
			exit(1);
		}
		value = gap->label->location - gap->command_location;
		if (gap->size == DIR_SIZE)
			encode_4_bytes(champion, LC, value);
		else
			encode_2_bytes(champion, LC, value);
}

void	assemble_op(unsigned char *champ, int *LC, t_pqueue *gaps, t_instruction *instruction)
{
	int		i;
	t_gap	*gap;

	i = 0;
	champ[(*LC)++] = instruction->op->opcode;
	if (instruction->op->has_pcode)
		champ[(*LC)++] = encode_param_byte(instruction);
	while (i < instruction->len)
	{
		if (instruction->arguments[i].type == T_LAB)
		{
			gap = pqueue_pop(gaps);
			fill_gap(champ, LC, gap);
			free(gap);
		}
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
			printf("\n\nThe arg value is %d and name %s\n\n", instruction->arguments[i].value, instruction->arguments[i].name);
			encode_1_byte(champ, LC, instruction->arguments[i].value);
		}
		i++;
		printf("inside assemble_op the LC is %d\n", *LC);
	}	
}
