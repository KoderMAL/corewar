/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 17:04:51 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/21 17:50:50 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				shift_loc(t_thread *pc, int amount)
{
	return ((pc->location + amount) % MEM_SIZE);
}

unsigned char	get_byte_at(t_thread *pc, int shift)
{
	return (pc->vm->map[shift_loc(pc, shift)]);
}

int				get_bytes(t_thread *pc, int shift, int bytes)
{
	int		param;

	param = 0;
	if (bytes == 1)
	{
		if (param > 0x7f)
			param |= 0xffffff00;
		param = get_byte_at(pc, shift);
	}
	else if (bytes == 2)
	{
		param = get_byte_at(pc, shift) << 8 | get_byte_at(pc, shift + 1);
		if (param > 0x7fff)
			param |= 0xffff0000;
	}
	else if (bytes == 4)
		param = get_byte_at(pc, shift) << 24 | get_byte_at(pc, shift + 1) << 16 |
			get_byte_at(pc, shift + 2) << 8 | get_byte_at(pc, shift + 3);
	return (param);
}

int			get(t_thread *pc, int param_nbr, bool long_range)
{
	int		type;
	int		param;
	
	type = pc->params_type[param_nbr];
	param = pc->params[param_nbr];
	if (type == T_REG)
		return (pc->r[param]);
	else if (type == T_DIR)
		return (param);
	else if (type == T_IND)
	{
		if (!long_range)
			param = (param < 0) ? param % -IDX_MOD : param % IDX_MOD;
		return (get_bytes(pc, param, 4));
	}
	return (-1);
}
