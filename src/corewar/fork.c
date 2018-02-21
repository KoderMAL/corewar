/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 11:24:05 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/21 17:44:37 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		op_fork(t_thread *pc)
{
	int		index;

	index = get(pc, 0, false);
	pqueue_push(&(pc->vm->threads), dup_thread(pc, shift_loc(pc, index)));
}
