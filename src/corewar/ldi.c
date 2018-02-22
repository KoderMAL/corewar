/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 18:33:18 by dhadley           #+#    #+#             */
/*   Updated: 2018/02/21 17:45:24 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Cette opération modifie le carry. ldi 3,%4,r1 lit IND_SIZE octets
** a l’adresse :
** (pc + (3 % IDX_MOD)) ajoute 4 à cette valeur. On nommera S cette somme.
** On lit REG_SIZE octet à l’adresse (pc + (S % IDX_MOD)) que l’on
** copie dans r1.
** Les paramètres 1 et 2 sont des index.
*/

void		op_ldi(t_thread *pc)
{
	int index;
	int value;

	index = get(pc, 0, false) + get(pc, 1, false);
	pc->params[3] = index;
	pc->params_type[3] = T_IND;
	value = get(pc, 3, false);
	set(pc, 2, value);
}
