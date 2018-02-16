/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 17:58:09 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/16 17:08:59 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Déplace le PC pour le placer sur le T_DIR à récupérer.
** Récupère le T_DIR sur 2 octets.
** Si carry à 1, place le PC à l'index donné.
** Si carry à 0, déplace le PC à la fin du T_DIR récupéré.
** Décrémente le process de 20 cycles (coût d'un zjmp).
*/

void	op_zjmp(t_thread *process)
{
	short	index;
	t_vm *vm;

	vm = process->vm;
	print_instruction_start(vm, process);
	print_str(vm, "zjmp ", 0);
	process->location = (process->location + 1) % MEM_SIZE;
	index = vm->map[process->location] << 8
			| vm->map[(process->location + 1) % MEM_SIZE];
	print_nbr(vm, index, 0);
	if (process->carry == 1)
	{
		process->location = (process->location + (index % IDX_MOD)) % MEM_SIZE;
		print_str(vm, " OK", 1);
	}
	else
	{
		process->location = (process->location + 2) % MEM_SIZE;
		print_str(vm, " FAILED", 1);
	}
	process->cycles -= 20;
	return ;
}
