/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 11:18:58 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/23 21:09:15 by stoupin          ###   ########.fr       */
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
	int		index;

	index = get(pc, 0, true);
	pqueue_push(&(pc->vm->threads), dup_thread(pc, shift_loc(pc, index)));
}
