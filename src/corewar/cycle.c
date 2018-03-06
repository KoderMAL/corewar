/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 11:51:04 by dhadley           #+#    #+#             */
/*   Updated: 2018/03/05 17:45:21 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "vm.h"

void					advance(t_thread *pc, bool silent)
{
	if (!silent)
		print_adv(pc->vm, pc);
	pc->location = shift_loc(pc, pc->shift);
	pc->shift = 0;
}

void					manage_countdown(t_thread *pc)
{
	if (pc->countdown <= 0)
	{
		if (pc->countdown == 0)
		{
			if (get_params_type(pc, pc->op) & get_params(pc, pc->op) &&
				!(pc->vm->zaz_mode && pc->op->opcode == O_AFF))
				do_op(pc->vm, pc);
			advance(pc, false);
			pc->countdown = -1;
			pc->op = NULL;
		}
		else if ((pc->op = get_op_by_code(pc->vm->map[pc->location])) != NULL)
		{
			pc->countdown = (pc->op->n_cycles - 2);
		}
		else
		{
			pc->shift = 1;
			advance(pc, true);
		}
	}
	else
		pc->countdown--;
}

static void				check_countdown(t_vm *vm)
{
	t_thread			*pc;
	t_pqueue_elem		*pq;

	pq = (vm->threads.last);
	while (pq)
	{
		pc = pq->p;
		manage_countdown(pc);
		pq = pq->prev;
	}
}

/*
** kill every thread
*/

void					tatatatata(t_vm *vm)
{
	t_pqueue_elem	*elem;
	t_thread		*victim;

	elem = vm->threads.first;
	while (elem)
	{
		victim = (t_thread*)elem->p;
		victim->alive = false;
		elem = elem->next;
	}
	vm->cycle_to_die = 0;
}

void					war_cycle(t_vm *vm)
{
	vm->something_happened = 0;
	dump(vm);
	vm->game_cycle++;
	if (vm->game_cycle == INT_MAX || vm->err != 0)
		vm_clean(vm);
	if (vm->threads.len == 0)
		print_winner(vm);
	if (vm->game_cycle > 0)
	{
		print_str(vm, "It is now cycle ", 0);
		print_nbr(vm, vm->game_cycle, 1);
	}
	check_countdown(vm);
	if (vm->base_cycle_to_die < 0 && vm->cycle_to_die == 0)
		tatatatata(vm);
	check_cycles(vm);
	if (vm->base_cycle_to_die < 0)
		tatatatata(vm);
}
