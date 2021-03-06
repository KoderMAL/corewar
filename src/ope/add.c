/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 12:10:18 by lramirez          #+#    #+#             */
/*   Updated: 2018/03/05 18:31:30 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar/vm.h"

/*
** Prend trois registres, additionne les 2 premiers,
** et met le résultat dans le troisième.
*/

void	op_add(t_thread *pc)
{
	int		a;
	int		b;
	int		result;

	a = get(pc, 0, false);
	b = get(pc, 1, false);
	result = a + b;
	set(pc, 2, result);
	if (result == 0)
		pc->carry = 1;
	else
		pc->carry = 0;
}
