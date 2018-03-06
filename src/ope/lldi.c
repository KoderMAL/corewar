/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 18:33:36 by dhadley           #+#    #+#             */
/*   Updated: 2018/03/06 17:35:34 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar/vm.h"

/*
** Comme ldi sans le %IDX_MOD Cette opération modifie le carry.
** ldi = Cette opération modifie le carry. ldi 3,%4,r1 lit IND_SIZE
** octets a l’adresse :
** (pc + (3 % IDX_MOD)) ajoute 4 à cette valeur. On nommera S cette somme.
** On lit REG_SIZE octet à l’adresse (pc + (S % IDX_MOD))
** que l’on copie dans r1.
** Les paramètres 1 et 2 sont des index.
*/

void		op_lldi(t_thread *pc)
{
	int index;
	int value;

	index = get(pc, 0, true) + get(pc, 1, true);
	print_instruction_continue(pc->vm);
	print_str(pc->vm, "-> load from ", 0);
	print_nbr(pc->vm, get(pc, 0, false), 0);
	print_str(pc->vm, " + ", 0);
	print_nbr(pc->vm, get(pc, 1, false), 0);
	print_str(pc->vm, " = ", 0);
	print_nbr(pc->vm, index, 0);
	print_str(pc->vm, " (with pc ", 0);
	print_nbr(pc->vm, pc->location + index, 0);
	print_str(pc->vm, ")", 0);
	pc->params[3] = index;
	pc->params_type[3] = T_IND;
	value = get(pc, 3, true);
	set(pc, 2, value);
	if (value == 0)
		pc->carry = 1;
	else
		pc->carry = 0;
}
