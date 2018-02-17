/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 17:58:09 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/17 14:53:23 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		op_zjmp(t_thread *pc)
{
	short	index;

	index = get(pc, 0);
	pc->location += (index < 0) ? shift_loc(pc, (index % -IDX_MOD)) :
		shift_loc(pc, (index % IDX_MOD));
	pc->indent = 0;

}