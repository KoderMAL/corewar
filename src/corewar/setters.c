/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 17:04:51 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/16 18:01:40 by lramirez         ###   ########.fr       */
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
	
	type = pc->params_type[param_nbr];
	param = pc->params[param_nbr];
	if (type == T_REG)
		pc->r[param] = value;
	else if (type == T_IND)
		set_bytes(pc, param, value);
}