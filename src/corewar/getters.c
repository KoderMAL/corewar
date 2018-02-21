/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 17:04:51 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/21 16:59:39 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				get_byte_at(t_thread *pc, int shift)
{
	return (pc->vm->map[shift_loc(pc, shift)]);
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
