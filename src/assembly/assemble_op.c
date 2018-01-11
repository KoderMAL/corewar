/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 18:39:49 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/11 19:16:08 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembly.h"

void	assemble_op(unsigned char *champ, int *LC, t_pqueue *gaps, t_pqueue args, t_instruction *instruction)
{
	char	param_byte;
	t_argument	*tmp;
	int		i;

	i = 0;
	champ[(*LC)++] = instruction->op.opcode;
	if (instruction->op.has_pcode)
		champ[(*LC)++] = encode_param_byte(args);
	tmp = args->first->p;
	while (i++ < args.len)
	{
		if (tmp.type == T_LAB)
			store_gap(LC, gaps, tmp, instruction->op.has_idx);
		else if (tmp.type == T_DIR)
		{
			if (instruction->op.has_idx)
				encode_2_bytes(champ, LC, tmp.value);
			else
				encode_4_bytes(champ, LC, tmp.value);
		}
		else if (tmp.type == T_IND)
			encode_2_bytes(champ, LC, tmp.value);
		else if (tmp.type == T_REG)
			encode_1_byte(champ, LC, tmp.value);
		tmp = tmp->next;
	}	

}
