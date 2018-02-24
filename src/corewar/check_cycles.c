/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cycles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 16:17:49 by dhadley           #+#    #+#             */
/*   Updated: 2018/02/16 14:24:35 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	kill_process(t_vm *vm)
{
	t_thread		*pc;
	t_pqueue_elem	*pq;
	t_pqueue_elem	*tmp;
	int				i;

	i = 0;
	pq = vm->threads.first;
	while (pq)
	{
		tmp = pq->next;
		pc = pq->p;
		if (pc->alive == true)
			pc->alive = false;
		else
		{
			pqueue_remove(&(vm->threads), pq);
			free(pc);
		}
		pq = tmp;
		i++;
	}
}

static void	find_winner(t_vm *vm)
{
	int		i;
	int		last;

	i = 0;
	last = vm->champs[i].last_live;
	while (i < 0)
	{
		if (vm->champs[i].last_live > last)
			vm->winner = i;
		i++;
	}
}

static void	print_winner(t_vm *vm)
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
	if (vm->game_cycle == 0)
		return ;
	if (vm->cycle_to_die <= 0)
	{
		print_winner(vm);
		return ;
	}
	else if (vm->threads.len == 0)
	{
		print_winner(vm);
		return ;
	}
	else if (vm->game_cycle % vm->cycle_to_die == 0)
	{
		kill_process(vm);
		if (vm->num_lives >= NBR_LIVE || vm->num_checkups == MAX_CHECKS)
		{
			vm->cycle_to_die -= CYCLE_DELTA;
			vm->num_checkups = -1;
		}
		vm->num_checkups++;
		vm->num_lives = 0;
	}
}
