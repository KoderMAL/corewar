/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 18:33:27 by dhadley           #+#    #+#             */
/*   Updated: 2018/02/23 21:09:39 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** comme ld sans le %IDX_MOD Cette opération modifie le carry.
** ld = Cette instruction prend 2 paramètres, le deuxième est forcément un
** registre (pas le pc).
** Elle load la valeur du premier paramètre dans le registre. Cette opération
** modifie le carry.
** ld 34,r3 charge les REG_SIZE octets à partir de l’adresse
** (pc + (34 % IDX_MOD)) dans le registre r3.
*/

void		op_lld(t_thread *pc)
{
	int value;

	value = get(pc, 0, true);
	set(pc, 1, value);
	if (value == 0)
		pc->carry = 1;
	else
		pc->carry = 0;
}
