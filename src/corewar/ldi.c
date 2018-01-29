/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 11:22:42 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/29 14:24:14 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
Cette opération modifie le carry. ldi 3,%4,r1 lit IND_SIZE octets a l’adresse :
(PC + (3 % IDX_MOD)) ajoute 4 à cette valeur. On nommera S cette somme. 
On lit REG_SIZE octet à l’adresse (PC + (S % IDX_MOD)) que l’on copie dans r1. 
Les paramètres 1 et 2 sont des index.
*/

/*
p1 = T_REG | T_DIR | T_IND
p2 = T_DIR | T_REG
p3 = T_REG

dir is on 2
*/

/*
if p1 = T_REG, check if valid reg on 1 oct. get value. store as p1.


if p1 = T_DIR, read value on 2 bytes. p1 = that value;

if p1 = T_IND, read two bytes. Go fetch the value IND_SIZE at the address (PC + (tmp_ind % IDXMOD)). p1 = that value

if p2 =T_DIR, read 2 bytes. p2 = that value. sum =p1 + p2;
if p2 = T_REG, read 1 byte. check if valid reg. get value. sum = p1 + p2;

read REG_SIZE bytes at the address (PC + (sum % IDX_MOD)) 

if p3 = T_REG, read 1 byte. check if valid reg. get value. r[x] = sum
*/


int	op_ldi(t_vm *vm, t_thread *PC)
{
	int	param1;
	int param2;
	int	sum;
	int	tmp;

	//assuming that the PX->location should be on the opcode
	if (check_params(vm->map[(PC->location + 1) % MEM_SIZE], 1) == IND_CODE)
	{
		tmp = recup_param(vm, (PC->location + 2) % MEM_SIZE, IND_SIZE);
		param1 = recup_param(vm, (PC->location + (tmp % IDX_MOD)) % MEM_SIZE, IND_SIZE);
		if (check_params(vm->map[(PC->location + 1) % MEM_SIZE], 2) == DIR_CODE)
		{
			param2 = recup_param(vm, (PC->location + 1 + 3) % MEM_SIZE, IND_SIZE);
			sum = param1 + param2;
			tmp = recup_param(vm, (PC->location + (sum % IDX_MOD)) % MEM_SIZE, REG_SIZE);
			if (check_params(vm->map[(PC->location + 1) % MEM_SIZE], 3) == REG_CODE)
			{
				param1 = recup_param(vm, (PC->location + 1 + 3 + 2) % MEM_SIZE, 1);
				if (param1 > REG_NUMBER || param1 < 1)
					return (0);
				PC->r[param1] = tmp;
				//			01	37	00 03	00 05	06
			}
		}
		else if (check_params(vm->map[(PC->location + 1) % MEM_SIZE], 2) == REG_CODE)
		{
			tmp = recup_param(vm, (PC->location + 1 + 3) % MEM_SIZE, 1);
			if (tmp > REG_NUMBER || tmp < 1)
				return (0);
			param2 = PC->r[tmp];
			sum = param1 + param2;
		}
	}
}
