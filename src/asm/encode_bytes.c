/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_bytes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 15:26:53 by dhadley           #+#    #+#             */
/*   Updated: 2018/03/06 18:06:52 by dhadley          ###   ########.fr       */
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
		if (instruction->arguments[i].type == T_DIR ||
			(instruction->arguments[i].type == T_LAB
				&& instruction->arguments[i].lab_type == T_DIR))
			param_byte |= DIR_CODE;
		if (instruction->arguments[i].type == T_IND ||
			(instruction->arguments[i].type == T_LAB
				&& instruction->arguments[i].lab_type == T_IND))
			param_byte |= IND_CODE;
		i++;
	}
	param_byte <<= (8 - (i * 2));
	return (param_byte);
}

void			encode_1_byte(unsigned char *champ, int *lc, int value)
{
	if (value < 0)
		value = ~(-value);
	champ[(*lc)++] = (unsigned char)value;
}

void			encode_2_bytes(unsigned char *champ, int *lc, int value)
{
	if (value < 0)
	{
		value = ~(-value);
		value++;
	}
	champ[(*lc)++] = ((value >> 8) & 255);
	champ[(*lc)++] = (value & 255);
}

void			encode_4_bytes(unsigned char *champ, int *lc, int value)
{
	if (value < 0)
	{
		value = ~(-value);
		value++;
	}
	champ[(*lc)++] = (value >> 24);
	champ[(*lc)++] = ((value >> 16) & 255);
	champ[(*lc)++] = ((value >> 8) & 255);
	champ[(*lc)++] = (value & 255);
}

void			encode_bytes(unsigned char *champ, int *lc, int value, int n)
{
	if (n == 1)
		encode_1_byte(champ, lc, value);
	if (n == 2)
		encode_2_bytes(champ, lc, value);
	if (n == 4)
		encode_4_bytes(champ, lc, value);
}
