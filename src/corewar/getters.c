/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 17:04:51 by lramirez          #+#    #+#             */
/*   Updated: 2018/03/02 14:21:52 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				shift_loc(t_thread *pc, int amount)
{
	int location;

	if (pc->location + amount < 0)
		location = (pc->location + amount) % MEM_SIZE + MEM_SIZE;
	else
		location = (pc->location + amount) % MEM_SIZE;
	return (location);
}

unsigned char	get_byte_at(t_thread *pc, int shift)
{
	return (pc->vm->map[shift_loc(pc, shift)]);
}

int				get_bytes(t_thread *pc, int s, int bytes)
{
	int		param;

	param = 0;
	if (bytes == 1)
	{
		param = get_byte_at(pc, s);
		if (param > 0x7f)
			param |= 0xffffff00;
	}
	else if (bytes == 2)
	{
		param = get_byte_at(pc, s) << 8 | get_byte_at(pc, s + 1);
		if (param > 0x7fff)
			param |= 0xffff0000;
	}
	else if (bytes == 4)
		param = get_byte_at(pc, s) << 24 | get_byte_at(pc, s + 1) << 16 |
			get_byte_at(pc, s + 2) << 8 | get_byte_at(pc, s + 3);
	return (param);
}

int				get(t_thread *pc, int param_nbr, bool long_range)
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
			param %= IDX_MOD;
		return (get_bytes(pc, param, 4));
	}
	return (-1);
}
