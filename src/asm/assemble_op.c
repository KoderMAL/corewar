/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 18:39:49 by dhadley           #+#    #+#             */
/*   Updated: 2018/02/08 11:30:42 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "util/pqueue.h"
#include "assembly.h"

int		assemble_op_fake(t_env *env, int *lc, t_pqueue *gaps,
							t_instruction *instruction)
{
	int		i;
	int		gaplc;

	gaplc = *lc;
	(*lc)++;
	if (instruction->op->has_pcode)
		(*lc)++;
	i = -1;
	while (++i < instruction->len)
	{
		if (instruction->arguments[i].type == T_LAB)
		{
			if (pqueue_push(gaps, create_gap(lc, instruction->arguments[i],
						instruction->op->has_idx, gaplc)))
				return (err(env, "memory error", -1));
		}
		else if (instruction->arguments[i].type == T_DIR)
			(*lc) += 2 * (2 - instruction->op->has_idx);
		else if (instruction->arguments[i].type == T_IND)
			(*lc) += 2;
		else if (instruction->arguments[i].type == T_REG)
			(*lc)++;
	}
	return (0);
}

void	fill_gap(unsigned char *champion, int *lc, t_gap *gap)
{
	int				value;

	value = gap->label->location - gap->command_location;
	if (gap->size == DIR_SIZE)
		encode_4_bytes(champion, lc, value);
	else
		encode_2_bytes(champion, lc, value);
}

void	assemble_op(t_env *env, int *lc, t_pqueue *gaps,
						t_instruction *instruction)
{
	int		i;
	t_gap	*gap;

	env->champion[(*lc)++] = instruction->op->opcode;
	if (instruction->op->has_pcode)
		env->champion[(*lc)++] = encode_param_byte(instruction);
	i = -1;
	while (++i < instruction->len)
	{
		if (instruction->arguments[i].type == T_LAB)
		{
			gap = pqueue_pop(gaps);
			fill_gap(env->champion, lc, gap);
			free(gap);
		}
		else if (instruction->arguments[i].type == T_DIR)
			encode_bytes(env->champion, lc, instruction->arguments[i].value,
							2 * (2 - instruction->op->has_idx));
		else if (instruction->arguments[i].type == T_IND)
			encode_2_bytes(env->champion, lc, instruction->arguments[i].value);
		else if (instruction->arguments[i].type == T_REG)
			encode_1_byte(env->champion, lc, instruction->arguments[i].value);
	}
}
