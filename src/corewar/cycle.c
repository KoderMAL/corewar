/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 11:51:04 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/31 11:57:24 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "vm.h"

static void		check_cycles(t_vm *vm)
{	
	(void)(vm);
}

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
	if (vm->op->opcode == 1)
		op_live(vm, pc);
	else if (vm->op->opcode == 2)
		op_ld(vm, pc);
	else if (vm->op->opcode == 4)
		op_add(vm, pc);
	else if (vm->op->opcode == 5)
		op_sub(vm, pc);
	else if (vm->op->opcode == 6)
		op_and(vm, pc);
	else if (vm->op->opcode == 9)
		op_zjmp(vm, pc);
	else if (vm->op->opcode == 12)
	 	op_fork(vm, pc);
	else if (vm->op->opcode == 16)
		op_aff(vm, pc);
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
	printf("pc->countdown=%d\n", pc->countdown);
		if (pc->countdown == -1)
		{
			printf("PC LOCATION DANS MAP:%d\n", pc->location);
			if ((vm->op = find_opcode(vm->map[pc->location])) != NULL)
			{
				printf("OPNAME:%s\n", vm->op->name);
				printf("OPcode:%d\n", vm->op->opcode);
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

void		war_cycle(t_vm *vm)
{
	if (vm->game_cycle == INT_MAX || vm->err != 0)
		vm_clean(vm);
	printf("\n---CYCLE++---\n");
	check_cycles(vm);
	check_countdown(vm);
	printf("CHECK\n");
	dump(vm);
	vm->game_cycle++;
}

/*
** Pseudocode for each cycle **
*
--------------

ft_check_cycles(t_vm *vm, cycles)
{
	//check if delta--
	for each threads
		//check nbr lives stuff
		//check if thread is dead (and pop)
}
 
--------------*/