/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 18:34:00 by dhadley           #+#    #+#             */
/*   Updated: 2018/03/05 18:31:43 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar/vm.h"

/*
** sti r2,%4,%5 sti copie REG_SIZE octet de r2 a l’adresse (4 + 5)
** Les paramètres 2 et 3 sont des index.
** Si les paramètres 2 ou 3 sont des registres, on utilisera leur
** contenu comme un index.
**
** p1 = T_REG
** p2 = T_REG | T_DIR | T_IND
** p3 = T_DIR | T_REG
**
** this function does not modify the carry
*/

void		op_sti(t_thread *pc)
{
	int index;
	int value;

	index = get(pc, 1, false) + get(pc, 2, false);
	pc->params[3] = index % IDX_MOD;
	pc->params_type[3] = T_IND;
	value = get(pc, 0, false);
	set(pc, 3, value);
	print_instruction_continue(pc->vm);
	print_str(pc->vm, "-> store to ", 0);
	print_nbr(pc->vm, get(pc, 1, false), 0);
	print_str(pc->vm, " + ", 0);
	print_nbr(pc->vm, get(pc, 2, false), 0);
	print_str(pc->vm, " = ", 0);
	print_nbr(pc->vm, index, 0);
	print_str(pc->vm, " (with pc and mod ", 0);
	print_nbr(pc->vm, pc->location + index % IDX_MOD, 0);
	print_str(pc->vm, ")", 0);
}
