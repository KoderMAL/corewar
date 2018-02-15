/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 14:39:27 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/13 20:37:17 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** op_xor détermine le type du premier paramètre (T_DIR, T_IND ou T_REG).
** Execute la fonction correspondante.
** Chaque fonction récupère les paramètres un à un selon leur type.
** Déplace le PC à la fin du dernier paramètre récupéré.
** Place le résultat de [param_1 ^ param_2] dans param_3.
** Met le carry à 1 et décrémente le process de 6 cycles (coût d'un xor).
*/

int				op_xor(t_vm *vm, t_thread *pc)
{
	pc->location = (pc->location + 1) % MEM_SIZE;
	if (check_params(vm->map[pc->location], 1) == DIR_CODE)
		return (get_dir_one(vm, pc, 2));
	else if (check_params(vm->map[pc->location], 1) == IND_CODE)
		return (get_ind_one(vm, pc, 2));
	else if (check_params(vm->map[pc->location], 1) == REG_CODE)
		return (get_reg_one(vm, pc, 2));
	else
		return (and_or_xor_exit(pc));
}
