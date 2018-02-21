/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 17:04:51 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/21 11:52:02 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				get_byte_at(t_thread *pc, int amount, bool shift)
{
	if (shift)
		return (pc->vm->map[shift_loc(pc, pc->shift + amount)]);
	else
		return (pc->vm->map[shift_loc(pc, amount)]);
}

int			get(t_thread *pc, int param_nbr)
{
	int		type;
	int		param;
	
	type = pc->params_type[param_nbr];
	param = pc->params[param_nbr];
	if (type == T_REG)
	{
		print_reg(pc->vm, param, 0);
		return (pc->r[param]);
	}
	else if (type == T_DIR)
	{
		print_nbr(pc->vm, param, 0);
		return (param);
	}
	else if (type == T_IND)
	{
		print_nbr(pc->vm, pc->vm->map[param], 0);
		return (pc->vm->map[param]);
	}
	return (-1);
}
