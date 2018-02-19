/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 14:39:27 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/19 11:00:21 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			op_xor(t_thread *pc)
{
	int		a;
	int		b;
	int		result;

	a = get(pc, 0);
	b = get(pc, 1);
	result = a ^ b;
	set(pc, 2, result);
	if (result == 0)
		pc->carry = 1;
}
