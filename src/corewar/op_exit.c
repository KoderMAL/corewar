/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 17:03:46 by dhadley           #+#    #+#             */
/*   Updated: 2018/02/23 21:10:03 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** op_exit puts the pc->carry to 0 if carry is set to true
** then decrements the pc->cycles by cycles
** and changes the pc->location to pc->location + 1
** before returning 0 to show the op has failed
*/

int	op_exit(t_thread *pc, int cycles, bool carry)
{
	if (carry == true)
		pc->carry = 0;
	pc->cycles -= cycles;
	pc->location = (pc->location + 1) % MEM_SIZE;
	return (0);
}
