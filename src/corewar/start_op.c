/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 13:27:28 by dhadley           #+#    #+#             */
/*   Updated: 2018/02/19 11:36:05 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	start_op(t_vm *vm, t_thread *pc)
{
	if (get_params(pc, pc->op))
		do_op(vm, pc);
	else
		pc->shift = 1;
	shift_loc(pc, pc->shift);
}
