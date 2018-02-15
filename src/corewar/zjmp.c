/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 17:58:09 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/15 12:29:51 by stoupin          ###   ########.fr       */
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

int	op_zjmp(t_vm *vm, t_thread *process)
{
	short	index;

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
	return (1);
}
