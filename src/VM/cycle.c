/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 11:51:04 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/26 18:42:00 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
//	printf("LIVE FOR TODAY:\n");
	live(vm, pc);
//	up_ld(vm, pc)
	printf("out\n");
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
	printf("pc->countdown%d\n", pc->countdown);
		if (pc->countdown == -1)
		{
			if ((vm->op = find_opcode(vm->map[pc->location])) != NULL)
			{
				pc->countdown = vm->op->n_cycles;
				pc->location++;
			}
			else
				pc->location++;
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

void		war(t_vm *vm)
{
	while (vm->game_cycle < INT_MAX)
	{
		check_cycles(vm);
		check_countdown(vm);
		dump(vm);
		vm->game_cycle++;
	}
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