/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:35:16 by alalaoui          #+#    #+#             */
/*   Updated: 2018/03/05 17:35:28 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static const t_op_assoc	g_op_assoc[16] = {
	{1, &op_live, 0},
	{2, &op_ld, 0},
	{3, &op_st, PARAM2 | PARAM3},
	{4, &op_add, 0},
	{5, &op_sub, 0},
	{6, &op_and, PARAM1 | PARAM2},
	{7, &op_or, PARAM1 | PARAM2},
	{8, &op_xor, PARAM1 | PARAM2},
	{9, &op_zjmp, 1},
	{10, &op_ldi, PARAM1 | PARAM2},
	{11, &op_sti, PARAM2 | PARAM3},
	{12, &op_fork, 0},
	{13, &op_lld, 0},
	{14, &op_lldi, PARAM1 | PARAM2},
	{15, &op_lfork, 0},
	{16, &op_aff, 0}
};

int						find_opcode(int pc)
{
	int		i;

	i = 0;
	while (i < 16)
	{
		if (g_op_tab[i].opcode == pc)
			return (i);
		i++;
	}
	return (-1);
}

void					do_op(t_vm *vm, t_thread *pc)
{
	int		i;

	i = find_opcode(pc->op->opcode);
	print_op(vm, pc, g_op_assoc[i].print_value);
	g_op_assoc[i].op_function(pc);
	print_str(vm, "", 1);
	vm->something_happened = 1;
}
