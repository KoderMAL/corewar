/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 11:51:04 by dhadley           #+#    #+#             */
/*   Updated: 2018/02/23 21:02:51 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "vm.h"

static const t_op_assoc	g_op_assoc[16] = {
	{1, &op_live, 0},
	{2, &op_ld, 0},
	{3, &op_st, 1},
	{4, &op_add, 0},
	{5, &op_sub, 0},
	{6, &op_and, 0},
	{7, &op_or, 0},
	{8, &op_xor, 0},
	{9, &op_zjmp, 1},
	{10, &op_ldi, 0},
	{11, &op_sti, 1},
	{12, &op_fork, 0},
	{13, &op_lld, 0},
	{14, &op_lldi, 0},
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
	int		opcode;
	int		i;

	if (pc->op == NULL)
		return ;
	i = find_opcode(pc->op->opcode);
	if (i >= 0)
	{
		if (get_params(pc, &g_op_tab[i]))
		{
			print_op(vm, pc, g_op_assoc[i].print_as_direct);
			g_op_assoc[i].op_function(pc);
			print_str(vm, "", 1);
			print_adv(vm, pc);
		}
		else
		{
			if (g_op_tab[i].has_pcode)
				pc->carry = 0;
			pc->shift = 1;
		}
		pc->location = shift_loc(pc, pc->shift);
	}
	pc->countdown = -1;
}

static void				check_countdown(t_vm *vm)
{
	int				i;
	t_thread		*pc;
	t_pqueue_elem	*pq;

	i = 0;
	pq = (vm->threads.last);
	while (pq)
	{
		pc = pq->p;
		pc->number = vm->threads.len - i;
		if (pc->countdown == 0)
			do_op(vm, pc);
		if (pc->countdown == -1)
		{
			if ((pc->op = get_op_by_code(vm->map[pc->location])) != NULL)
				pc->countdown = (pc->op->n_cycles - 1);
			else
				pc->location = shift_loc(pc, 1);
		}
		else
			pc->countdown--;
		pq = pq->prev;
		i++;
	}
}

void					war_cycle(t_vm *vm)
{
	dump(vm);
	if (vm->game_cycle == INT_MAX || vm->err != 0)
		vm_clean(vm);
	check_cycles(vm);
	check_countdown(vm);
	vm->game_cycle++;
}
