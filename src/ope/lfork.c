/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 11:18:58 by lramirez          #+#    #+#             */
/*   Updated: 2018/03/06 17:31:10 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar/vm.h"

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
	new_thread->countdown = -1;
	print_str(pc->vm, " (", 0);
	print_nbr(pc->vm, pc->location + index, 0);
	print_str(pc->vm, ")", 0);
	pqueue_push(&(pc->vm->threads), new_thread);
}
