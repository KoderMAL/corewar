/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 14:39:27 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/21 18:47:29 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Cette opération est un OU bit-à-bit, suivant le même principe que and.
** and = Applique un & (ET bit-à-bit) sur les deux premiers paramètres,
** et stocke le résultat dans le registre qui est le 3ème paramètre.
*/

void		op_or(t_thread *pc)
{
	int		a;
	int		b;
	int		result;

	a = get(pc, 0, false);
	b = get(pc, 1, false);
	result = a | b;
	set(pc, 2, result);
	if (result == 0)
		pc->carry = 1;
	else
		pc->carry = 0;
}
