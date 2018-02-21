/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 11:51:04 by dhadley           #+#    #+#             */
/*   Updated: 2018/02/21 15:55:23 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "vm.h"
#include "op_assoc.h"

static const t_op_assoc	g_op_assoc[16] = {
	{1, &op_live},
	{2, &op_ld},
	{3, &op_st},
	{4, &op_add},
	{5, &op_sub},
	{6, &op_and},
	{7, &op_or},
	{8, &op_xor},
	{9, &op_zjmp},
	{10, &op_ldi},
	{11, &op_sti},
	{12, &op_fork},
	{13, &op_lld},
	{14, &op_lldi},
	{15, &op_lfork},
	{16, &op_aff}
};

int			find_opcode(int pc)
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

void			do_op(t_vm *vm, t_thread *pc)
{
	int		i;

	if (vm->op == NULL)
		return ;
	i = find_opcode(vm->op->opcode);
	if (i >= 0)
	{
		if (get_params(pc, &g_op_tab[i]))
		{
			print_op(vm, pc);
			g_op_assoc[i].op_function(pc);
			print_str(vm, "", 1);
		}
		else
		{
			if (g_op_tab[i].has_pcode)
				pc->carry = 0;
			pc->shift = 1;
		}
		shift_loc(pc, pc->shift);
	}
	pc->countdown = -1;
}

static void		check_countdown(t_vm *vm)
{
	int				i;
	t_thread		*pc;
	t_pqueue_elem	*pq;

	i = 0;
	pq = (vm->threads.last);
	while (i < vm->threads.len)
	{
		pc = pq->p;
		pc->number = i;

		if (pc->countdown == 0)
			do_op(vm, pc);
		if (pc->countdown == -1)
		{
			if ((vm->op = get_op_by_code(vm->map[pc->location])) != NULL)
				pc->countdown = (vm->op->n_cycles - 1);
			else
				pc->location = shift_loc(pc, 1);
		}
		else
			pc->countdown--;
		pq = pq->prev;
		i++;
	}
}

void			war_cycle(t_vm *vm)
{
	dump(vm);
	if (vm->game_cycle == INT_MAX || vm->err != 0)
		vm_clean(vm);
	check_cycles(vm);
	check_countdown(vm);
	vm->game_cycle++;
}
