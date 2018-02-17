/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 17:58:09 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/17 13:11:48 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		op_zjmp(t_thread *pc)
{
	short	index;

	index = get(pc, 0);
	pc->location += (index < 0) ? shift_loc(pc, (index % -IDX_MOD)) :
		shift_loc(pc, (index % IDX_MOD));
	pc->indent = 0;
}

	// short	index;
	// t_vm	*vm;

	// vm = pc->vm;
	// print_instruction_start(vm, c);
	// print_str(vm, "zjmp ", 0);
	// index = get(pc, 0);
	// print_nbr(vm, index, 0);
	// if (process->carry == 1)
	// {
	// 	process->location += (index < 0) ? shift_loc(pc, (index % -IDX_MOD)) :
	// 	shift_loc(pc, (index % IDX_MOD));
	// 	print_str(vm, " OK", 1);
	// }
	// else
	// {
	// 	process->location = (process->location + 2) % MEM_SIZE;
	// 	print_str(vm, " FAILED", 1);
	// }