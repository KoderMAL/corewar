/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cycles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 16:17:49 by dhadley           #+#    #+#             */
/*   Updated: 2018/02/13 13:37:42 by dhadley          ###   ########.fr       */
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

void		check_cycles(t_vm *vm)
{
	if (vm->game_cycle == 0)
		return ;
	if (vm->cycle_to_die <= 0)
		;//		printf("CYCLE TO DIE == 0 and game should end");
	else if (vm->threads.len == 0)
		;//		printf("vm->threads.len = 0 and we should end the game");
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
