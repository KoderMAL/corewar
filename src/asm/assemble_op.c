/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 18:39:49 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/23 17:32:21 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "util/pqueue.h"
#include "assembly.h"

int		assemble_op_fake(t_env *env, int *LC, t_pqueue *gaps, t_instruction *instruction)
{
	int		i;
	int		gapLC;

	gapLC = *LC;
	(*LC)++;
	if (instruction->op->has_pcode)
		(*LC)++;
	i = -1;
	while (++i < instruction->len)
	{
		if (instruction->arguments[i].type == T_LAB)
		{
			if (pqueue_push(gaps, create_gap(LC, instruction->arguments[i],
						instruction->op->has_idx, gapLC)))
				return (err(env, "memory error", -1));
		}
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
	}
	return (0);
}

void	fill_gap(unsigned char *champion, int *LC, t_gap *gap)
{
	int				value;

		// check that *LC == gap->location
/*		if (*LC != gap->location)
		{
			printf("ERROR: LC = %d, gap->location = %d\n", *LC, gap->location);
			exit(1);
		}
*/
		value = gap->label->location - gap->command_location;
		if (gap->size == DIR_SIZE)
			encode_4_bytes(champion, LC, value);
		else
			encode_2_bytes(champion, LC, value);
}

void	assemble_op(t_env *env, int *LC, t_pqueue *gaps, t_instruction *instruction)
{
	int		i;
	t_gap	*gap;

	env->champion[(*LC)++] = instruction->op->opcode;
	if (instruction->op->has_pcode)
		env->champion[(*LC)++] = encode_param_byte(instruction);
	i = -1;
	while (++i < instruction->len)
	{
		if (instruction->arguments[i].type == T_LAB)
		{
			gap = pqueue_pop(gaps);
			fill_gap(env->champion, LC, gap);
			free(gap);
		}
		else if (instruction->arguments[i].type == T_DIR)
		{
			if (instruction->op->has_idx)
				encode_2_bytes(env->champion, LC, instruction->arguments[i].value);
			else
				encode_4_bytes(env->champion, LC, instruction->arguments[i].value);
		}
		else if (instruction->arguments[i].type == T_IND)
			encode_2_bytes(env->champion, LC, instruction->arguments[i].value);
		else if (instruction->arguments[i].type == T_REG)
			encode_1_byte(env->champion, LC, instruction->arguments[i].value);
	}
}
