/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 14:39:27 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/21 17:44:37 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			op_and(t_thread *pc)
{
	int		a;
	int		b;
	int		result;

	a = get(pc, 0, false);
	b = get(pc, 1, false);
	result = a & b;
	set(pc, 2, result);
	if (result == 0)
		pc->carry = 1;
	else
		pc->carry = 0;
}
