/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_bytes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 15:26:53 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/10 18:39:13 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembly.h"

unsigned char	encode_param_byte(t_pqueue args)
{
	unsigned char	param_byte;
	t_argument		*tmp;
	int				i;

	i = 0;
	param_byte = 0;
	tmp = args->first->p;
	while (i < args.len)
	{
		param_byte << 2;
		if (tmp.type == T_REG)
			param_byte |= REG_CODE;
		if (tmp.type == T_DIR || (tmp.type == T_LAB && tmp.lab_type == T_DIR))
			param_byte |= DIR_CODE;
		if (tmp.type == T_IND || (tmp.type == T_LAB && tmp.lab_type == T_IND))
			param_byte |= IND_CODE;
		tmp = tmp->next;
		i++;
	}
	param_byte <<= (8 - (i * 2)); 
	return (param_byte);
}

void	encode_1_byte(unsigned char *champ, int *LC, int value)
{
	if (value < 0)
		value = ~(-value);
	champ[(*LC)++] = (unsigned char)value;
}

void	encode_2_bytes(unsigned char *champ, int *LC, int value)
{
	short			short_value;

	if (value < 0)
		value = ~(-value);
	short_value = (short)value;	
	champ[(*LC)++] = (short_value >> 8);
	champ[(*LC)++] = (short_value & 255);
}

void	encode_4_bytes(unsigned char *champ, int *LC, int value)
{
	if (value < 0)
		value = ~(-value);
	champ[(*LC)++] = (value >> 24);
	champ[(*LC)++] = ((value >> 16) & 255);
	champ[(*LC)++] = ((value >> 8) & 255);
	champ[(*LC)++] = (value & 255);
}
