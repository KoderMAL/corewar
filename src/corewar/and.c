/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 14:39:27 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/16 15:50:27 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			op_and(t_thread *pc)
{
	int		param[2];
	int		i;

	i = 0;
	while (i < 2)
	{
		if (pc->params_type[i] == T_REG)
			param[i] = pc->r[params[i]];
		else if (pc->params_type[i] == T_DIR)
			param[i] = params[i];
		else if (pc->params_type[i] == T_IND)
			param[i] = pc->vm->map[params[i]];
	}

	
	
	
	// pc->location = (pc->location + 1) % MEM_SIZE;
	// if (check_params(vm->map[pc->location], 1) == DIR_CODE)
	// 	return (get_dir_one(vm, pc, 0));
	// else if (check_params(vm->map[pc->location], 1) == IND_CODE)
	// 	return (get_ind_one(vm, pc, 0));
	// else if (check_params(vm->map[pc->location], 1) == REG_CODE)
	// 	return (get_reg_one(vm, pc, 0));
	// else
	// 	return (and_or_xor_exit(pc));
	if (pc)
		return ;
	return ;
}
