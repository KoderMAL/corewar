/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 11:18:58 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/25 17:00:31 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Pareil qu’un fork sans modulo à l'adresse.
** lfork = Crée un nouveau processus, qui hérite des différents états de son
** père, à part son PC, qui est mis à (PC + (1er paramètre % IDX_MOD)).
*/

void	op_lfork(t_thread *pc)
{
	int			index;
	t_thread	*new_thread;


	index = get(pc, 0, true);
	if (!(new_thread = dup_thread(pc, shift_loc(pc, index))))
		return ;
	if ((new_thread->op = get_op_by_code(pc->vm->map[new_thread->location])) != NULL)
		new_thread->countdown = new_thread->op->n_cycles - 1;
	else
	{
		new_thread->location = shift_loc(new_thread, 1);
		new_thread->countdown = -1;
	}
	pqueue_push(&(pc->vm->threads), new_thread);
	print_str(pc->vm, " (", 0);
	print_nbr(pc->vm, pc->location + index, 0);
	print_str(pc->vm, ")", 0);
}
