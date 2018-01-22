/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_bytes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 15:26:53 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/22 18:13:06 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembly.h"

unsigned char	encode_param_byte(t_instruction *instruction)
{
	unsigned char	param_byte;
	int				i;

	i = 0;
	param_byte = 0;
	while (i < instruction->len)
	{
		param_byte <<= 2;
		if (instruction->arguments[i].type == T_REG)
			param_byte |= REG_CODE;
		if (instruction->arguments[i].type == T_DIR || (instruction->arguments[i].type == T_LAB && instruction->arguments[i].lab_type == T_DIR))
			param_byte |= DIR_CODE;
		if (instruction->arguments[i].type == T_IND || (instruction->arguments[i].type == T_LAB && instruction->arguments[i].lab_type == T_IND)) // can remove lab_type check
			param_byte |= IND_CODE;
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

	if (value < 0 && value > -255)
	{
		value = ~(-value);
		value++;
	}
	else if (value < -255)
	{
		value = ~(-value);
		value++;
	}
//	short_value = (short)value;
	champ[(*LC)++] = ((value >> 8) & 255);
	champ[(*LC)++] = (value & 255);
}

void	encode_4_bytes(unsigned char *champ, int *LC, int value)
{
//	if (value < -255)
//		value++;
	if (value < 0)
	{
		value = ~(-value);
		value++;
	}
	champ[(*LC)++] = (value >> 24);
	champ[(*LC)++] = ((value >> 16) & 255);
	champ[(*LC)++] = ((value >> 8) & 255);
	champ[(*LC)++] = (value & 255);
}
