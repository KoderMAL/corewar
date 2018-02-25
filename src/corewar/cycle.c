/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 11:51:04 by dhadley           #+#    #+#             */
/*   Updated: 2018/02/24 20:39:48 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
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

	if (pc->op == NULL)
		return ;
	i = find_opcode(pc->op->opcode);
	if (i >= 0)
	{
		if (get_params(pc, &g_op_tab[i]))
		{
			print_op(vm, pc, g_op_assoc[i].print_value);
			g_op_assoc[i].op_function(pc);
			print_str(vm, "", 1);
		}
		else
		{
			if (g_op_tab[i].has_pcode)
				pc->carry = 0;
		}
	}
	else
		pc->shift = 1;
	print_adv(vm, pc);
	pc->location = shift_loc(pc, pc->shift);
	pc->countdown = -1;
}

static void				check_countdown(t_vm *vm)
{
	int				i;
	t_thread		*pc;
	t_pqueue_elem	*pq;

	i = vm->threads.len;
	pq = (vm->threads.last);
	while (pq)
	{
		pc = pq->p;
		pc->number = i;
		// if (pc->countdown == 0 && pc->location == 0x000a && ft_strcmp(pc->op->name, "fork") == 0)
		// 	printf("yo\n");
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
		i--;
	}
}

void					war_cycle(t_vm *vm)
{
	dump(vm);
	if (vm->game_cycle == INT_MAX || vm->err != 0)
		vm_clean(vm);
	if (vm->game_cycle > 0)
	{
		print_str(vm, "It is now cycle ", 0);
		print_nbr(vm, vm->game_cycle, 1);
	}
	check_cycles(vm);
	check_countdown(vm);
	vm->game_cycle++;
}
