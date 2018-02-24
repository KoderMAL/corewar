/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_success.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 17:09:22 by dhadley           #+#    #+#             */
/*   Updated: 2018/02/23 21:10:14 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** op_success puts the pc->carry to 1 if carry is true
** decrements the pc->cycles by cycles
** and changes the pc->location to pc->location + loc
** before returning 1 to show the op was a success
*/

int	op_success(t_thread *pc, int cycles, int loc, bool carry)
{
	if (carry == true)
		pc->carry = 1;
	pc->cycles -= cycles;
	pc->location = (pc->location + loc) % MEM_SIZE;
	return (1);
}
