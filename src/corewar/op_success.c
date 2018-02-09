/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_success.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 17:09:22 by dhadley           #+#    #+#             */
/*   Updated: 2018/02/09 17:46:57 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** op_success puts the pc->carry to 1 if carry is true
** decrements the pc->cycles by num_cycles
** and changes the pc->location to pc->location + location 
** before returning 1 to show the op was a success
*/

int	op_success(t_thread *pc, int num_cycles, int location, bool carry)
{
	if (carry == true)
		pc->carry = 1;
	pc->cycles -= num_cycles;
	pc->location = (pc->location + location) % MEM_SIZE;
	return (1);
}
