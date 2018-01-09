/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_bytes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 15:26:53 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/09 21:01:02 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembly.h"

char	encode_param_byte(t_pqueue args)
{
	char		param_byte;
	t_argument	*tmp;
	int			i;

	i = 0;
	param_byte = 0;
	tmp = args->first->p;
	while (i < args.len)
	{
		param_byte << 2;
		if (tmp.type == T_REG)
			param_byte |= 1;
		if (tmp.type == T_DIR || (tmp.type == T_LAB && tmp.lab_type == T_DIR))
			param_byte |= 2;
		if (tmp.type == T_IND || (tmp.type == T_LAB && tmp.lab_type == T_IND))
			param_byte |= 3;
		tmp = tmp->next;
		i++;
	}
	if (i == 1)
		param_byte << 6;
	else if (i == 2)
		param_byte << 4;
	else if (i == 3)
		param_byte << 2;
	return (param_byte);
}

char	*encode_2_bytes(int value)
{
	char	buf[2];
	short	short_value;

	ft_memset(buf, '\0', 2);
	short_value = (short)value;
	buf[0] = (short_value >> 8);
	buf[1] = (short_value & 255);
	return (buf);
}

char	*encode_4_bytes(int value)
{
	char	buf[4];

	ft_memset(buf, '\0', 4);
	buf[0] = (value >> 24);
	buf[1] = ((value >> 16) & 255);
	buf[2] = ((value >> 8) & 255);
	buf[3] = (value & 255);
	return (buf);
}
