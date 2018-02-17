/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 11:24:05 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/17 13:16:05 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		op_fork(t_thread *pc)
{
	int		index;

	index = get(pc, 0);
	index = (index < 0) ? shift_loc(pc, (index % -IDX_MOD)) :
		shift_loc(pc, (index % IDX_MOD));
	pqueue_push(&(pc->vm->threads), dup_thread(pc, shift_loc(pc, index)));
}
