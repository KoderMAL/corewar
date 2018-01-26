/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 16:50:31 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/26 15:10:38 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
/*
Cette instruction prend 2 paramètres, le deuxième est forcément un registre (pas le PC). 
Elle load la valeur du premier paramètre dans le registre. Cette opération modifie le carry.
ld 34,r3 charge les REG_SIZE octets à partir de l’adresse (PC + (34 % IDX_MOD)) dans le registre r3.
*/

static int	check_first_param(unsigned char byte)
{
	if ((byte >> 6) & DIR_CODE)
		return (DIR_CODE);
	else if ((byte >> 6) & IND_CODE)
		return (IND_CODE);
	else if (REG_CODE
			ret (REG_CODE)
	return (0);
}

int	op_ld(t_vm *vm, t_thread *PC)
{
	//assuming the PC->location should be on the byte after the opcode
	if (check_param_byte(vm->map[PC->location]))
	{

		PC->location++;

	}
}
