/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cycles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 16:17:49 by dhadley           #+#    #+#             */
/*   Updated: 2018/02/12 18:07:20 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	kill_process(t_vm *vm)
{
	t_thread		*pc;
	t_pqueue_elem	*pq;
	int				i;

	i = 0;
	pq = vm->threads.first;
	while (i < vm->threads.len)
	{
		pc = pq->p;
		if (pc->alive == true)
			pc->alive = false;
		else
			//pop PC;
		pq = pq->next;
		i++;
	}
}

void		check_cycles(t_vm *vm)
{
	if (vm->cycle_to_die == 0)
		;
		//end game
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
