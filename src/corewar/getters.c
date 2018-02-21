/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 17:04:51 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/21 15:30:15 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				get_byte_at(t_thread *pc, int amount)
{
	return (pc->vm->map[shift_loc(pc, pc->shift + amount)]);
}

int			get(t_thread *pc, int param_nbr)
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
		return (pc->vm->map[param]);
	return (-1);
}
