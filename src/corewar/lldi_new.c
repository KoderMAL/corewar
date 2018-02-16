/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 15:17:04 by dhadley           #+#    #+#             */
/*   Updated: 2018/02/16 18:17:10 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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

	index = get(pc, 0) + get(pc, 1);
	get


	int	param1;
	int	tmp;
	t_vm *vm;

	vm = pc->vm;
	if (check_params(vm->map[(pc->location + 1) % MEM_SIZE], 1) == IND_CODE)
	{
		tmp = recup_param(vm, (pc->location + 2) % MEM_SIZE, IND_SIZE);
		param1 = recup_param(vm, (pc->location + tmp) % MEM_SIZE, IND_SIZE);
		if (check_params(vm->map[(pc->location + 1) % MEM_SIZE], 2) == DIR_CODE)
			return ;//(second_dir(vm, pc, param1, tmp));
		else if (check_params(vm->map[(pc->location + 1) % MEM_SIZE], 2)
				== REG_CODE)
			return ;//(second_reg(vm, pc, param1, tmp));
	}
	else if (check_params(vm->map[(pc->location + 1) % MEM_SIZE], 1)
			== DIR_CODE)
		return ;//(op_lldi_dir(pc));
	else if (check_params(vm->map[(pc->location + 1) % MEM_SIZE], 1)
			== REG_CODE)
		return ;//(op_lldi_reg(pc));
	return (op_exit(pc, 50, true));
}
