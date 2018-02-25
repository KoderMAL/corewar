/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cycles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 16:17:49 by dhadley           #+#    #+#             */
/*   Updated: 2018/02/25 16:00:08 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		kill_process(t_vm *vm)
{
	t_thread		*pc;
	t_pqueue_elem	*pq;
	t_pqueue_elem	*tmp;

	pq = vm->threads.last;
	while (pq)
	{
		tmp = pq->prev;
		pc = pq->p;
		if (pc->alive == true)
			pc->alive = false;
		else
		{
			print_str(vm, "Process ", 0);
			print_nbr(vm, pc->number, 0);
			print_str(vm, " hasn't lived for ", 0);
			print_nbr(vm, vm->game_cycle - pc->last_live, 0);
			print_str(vm, " cycles (CTD ", 0);
			print_nbr(vm, vm->base_cycle_to_die, 0);
			print_str(vm, ")", 1);
			pqueue_remove(&(vm->threads), pq);
			free(pc);
		}
		pq = tmp;
	}
}

static void	find_winner(t_vm *vm)
{
	int		i;
	int		last;

	i = 0;
	last = vm->champs[i].last_live;
	while (i < vm->n_champs)
	{
		if (vm->champs[i].last_live >= last)
			vm->winner = i;
		i++;
	}
}

void		print_winner(t_vm *vm)
{
	if (vm->cycle_to_dump != -1)
		write_map(vm);
	find_winner(vm);
	openfile_write_str(&(vm->stdout), "Contestant ", 0);
	openfile_write_nbr(&(vm->stdout), vm->winner + 1, 0);
	openfile_write_str(&(vm->stdout), ", \"", 0);
	openfile_write_str(&(vm->stdout), vm->champs[vm->winner].name, 0);
	openfile_write_str(&(vm->stdout), "\", has won !", 1);
	vm_clean(vm);
}

void		check_cycles(t_vm *vm)
{
	if (vm->cycle_to_die == 0)
	{
		kill_process(vm);
		if (vm->num_lives >= NBR_LIVE || vm->num_checkups == MAX_CHECKS)
		{
			vm->base_cycle_to_die -= CYCLE_DELTA;
			print_str(vm, "Cycle to die is now ", 0);
			print_nbr(vm, vm->base_cycle_to_die, 1);
			vm->num_checkups = -1;
		}
		vm->cycle_to_die = vm->base_cycle_to_die;
		vm->num_checkups++;
		vm->num_lives = 0;
	}
	vm->cycle_to_die--;
}
