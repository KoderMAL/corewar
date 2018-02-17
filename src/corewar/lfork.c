/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 11:18:58 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/17 13:15:47 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_lfork(t_thread *pc)
{
	int		index;

	index = get(pc, 0);
	pqueue_push(&(pc->vm->threads), dup_thread(pc, shift_loc(pc, index)));
}
