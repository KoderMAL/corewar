/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 17:04:51 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/21 17:06:47 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		set_bytes(t_thread *pc, int param, int value)
{
	pc->vm->map[shift_loc(pc, param)] = (value >> 24);
	pc->vm->map[shift_loc(pc, param + 1)] = ((value >> 16) & 255);
    pc->vm->map[shift_loc(pc, param + 2)] = ((value >> 8) & 255);
    pc->vm->map[shift_loc(pc, param + 3)] = (value & 255);
}

void		set(t_thread *pc, int param_nbr, int value)
{
	int		type;
	int		param;
	int		location;

	type = pc->params_type[param_nbr];
	param = pc->params[param_nbr];
	if (type == T_REG)
		pc->r[param] = value;
	else if (type == T_DIR)
		set_bytes(pc, param, value);
	else if (type == T_IND)
	{
		param = (param < 0) ? shift_loc(pc, (param % -IDX_MOD))
				: shift_loc(pc, (param % IDX_MOD));
		location = get_bytes(pc, param, 4);
		set_bytes(pc, location, value);
	}
}
