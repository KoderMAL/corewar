/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 11:04:33 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/29 11:15:30 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	comme ld sans le %IDX_MOD Cette opération modifie le carry.
	ld = Cette instruction prend 2 paramètres, le deuxième est forcément un registre (pas le PC).
	Elle load la valeur du premier paramètre dans le registre. Cette opération modifie le carry.
	ld 34,r3 charge les REG_SIZE octets à partir de l’adresse (PC + (34 % IDX_MOD)) dans le registre r3.
*/

//need to modify the carry
//need to take off cycles from the PC cycle to die

int	op_lld(t_vm *vm, t_thread *PC)
{
	int	param1;
	int tmp_ind;
	int param2;

	//assuming the PC->location should be on the opcode
	if (check_params(vm->map[(PC->location + 1) % MEM_SIZE], 1) == DIR_CODE)
	{
		param1 = recup_param(vm, (PC->location + 2) % MEM_SIZE, 4);
		param2 = recup_param(vm, (PC->location + 2 + 4) % MEM_SIZE, 1);
		if (param2 > REG_NUMBER || param2 < 1)
			param2 = 0;
		PC->r[param2] = param1;
		PC->location = (PC->location + 1 + 1 + 4 + 1) % MEM_SIZE;
		return (1);
	}
	else if (check_params(vm->map[(PC->location + 1) % MEM_SIZE], 1) == IND_CODE)
	{
		tmp_ind = recup_param(vm, (PC->location + 2) % MEM_SIZE, 2);
		param1 = recup_param(vm, (PC->location + tmp_ind) % MEM_SIZE, REG_SIZE);
		param2 = recup_param(vm, (PC->location + 2 + 2) % MEM_SIZE, 1);
		if (param2 > REG_NUMBER || param2 < 1)
			param2 = 0;
		PC->r[param2] = param1;
		PC->location = (PC->location + 1 + 1 + 2 + 1) % MEM_SIZE;
		return (1);
	}
	return (0);
}
