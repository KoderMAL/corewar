/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 11:24:05 by lramirez          #+#    #+#             */
/*   Updated: 2018/03/05 18:31:35 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar/vm.h"

/*
** Crée un nouveau processus, qui hérite des différents états de son père,
** à part son PC, qui est mis à (PC + (1er paramètre % IDX_MOD)).
*/

void		op_fork(t_thread *pc)
{
	int			index;
	t_thread	*new_thread;

	index = get(pc, 0, false) % IDX_MOD;
	if (!(new_thread = dup_thread(pc, shift_loc(pc, index))))
		return ;
	new_thread->countdown = -1;
	pqueue_push(&(pc->vm->threads), new_thread);
	print_str(pc->vm, " (", 0);
	print_nbr(pc->vm, pc->location + index, 0);
	print_str(pc->vm, ")", 0);
}
