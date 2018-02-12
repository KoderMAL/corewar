/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 11:51:04 by dhadley           #+#    #+#             */
/*   Updated: 2018/02/12 18:33:54 by dhadley          ###   ########.fr       */
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

const t_op		*find_opcode(int pc)
{
	int	i;

	i = 0;
	while (g_op_tab[i].opcode != 0)
	{
		if (g_op_tab[i].opcode == pc)
			return (&(g_op_tab[i]));
		i++;
	}
	return (NULL);
}

static void		do_op(t_vm *vm, t_thread *pc)
{
	int	i;

	i = 1;
	while (i < 16)
	{
		if (vm->op->opcode == g_op_assoc[i].opcode)
			g_op_assoc[i].op_function(vm, pc);
		i++;
	}
}

static void		check_countdown(t_vm *vm)
{
	int				i;
	t_thread		*pc;
	t_pqueue_elem	*pq;

	i = 0;
	pq = (vm->threads.first);
	while (i < vm->threads.len)
	{
		pc = pq->p;
		//printf("pc->countdown=%d\n", pc->countdown); //
		if (pc->countdown == -1)
		{
			//printf("PC LOCATION DANS MAP:%d\n", pc->location); //
			if ((vm->op = find_opcode(vm->map[pc->location])) != NULL)
			{
				//printf("OPNAME:%s\n", vm->op->name); //
				//printf("OPcode:%d\n", vm->op->opcode); //
				pc->countdown = vm->op->n_cycles;
			}
			else
				pc->location = (pc->location + 1) % MEM_SIZE;
		}
		else if (pc->countdown == 0)
		{
			do_op(vm, pc);
			pc->countdown = -1;
		}
		else
			pc->countdown--;
		pq = pq->next;
		i++;
	}
}

void			war_cycle(t_vm *vm)
{
	if (vm->game_cycle == INT_MAX || vm->err != 0)
		vm_clean(vm);
	//printf("\n---CYCLE++---\n"); //
	check_cycles(vm);
	check_countdown(vm);
	dump(vm);
	vm->game_cycle++;
}
