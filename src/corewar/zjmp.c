/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 17:58:09 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/23 17:01:59 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Elle prendra un index, et fait un saut à cette adresse si le carry est à 1.
*/

void		op_zjmp(t_thread *pc)
{
	short	index;

	index = get(pc, 0, false);
	index %= IDX_MOD;
	if (pc->carry == 1)
	{
		pc->location = shift_loc(pc, index % IDX_MOD);
		pc->shift = 0;
		print_str(pc->vm, " OK", 0);
	}
	else
		print_str(pc->vm, " FAILED", 0);
}
