/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 17:58:09 by lramirez          #+#    #+#             */
/*   Updated: 2018/01/26 12:58:57 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"

// Déplace le PC pour le placer sur le T_DIR à récupérer.
// Récupère le T_DIR sur 2 octets (short).
// Si carry à 1, place le PC à l'index donné.
// Si carry à 0, déplace le PC à la fin du short récupéré.
// Décrémente le process de 20 cycles (coût d'un zjmp).

void		zjmp(t_vm *vm, t_thread process)
{
	short	index;

	process->location = (process->location + 1) % MEM_SIZE;
	index = vm->map[process->location] << 8 | vm->map[(process->location + 1) % MEM_SIZE];
	if (process->carry == 1)
		process->location = (process->location + (index % IDX_MOD)) % MEM_SIZE;
	else
		process->location = (process->location + 2) % MEM_SIZE;
	process->cycles -= 20;
}
