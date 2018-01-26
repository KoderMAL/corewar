/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lararamirez <lararamirez@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 17:58:09 by lramirez          #+#    #+#             */
/*   Updated: 2018/01/26 09:57:37 by lararamirez      ###   ########.fr       */
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

	process->location = (process->location + 4) % MEM_SIZE;
	index = map[process->location] << 8 | map[(process->location + 1) % MEM_SIZE];
	if (process->carry == 1)
		process->location = (process->location + (index % IDX_MOD)) % MEM_SIZE;
	else
		process->location = (process->location + 2) % MEM_SIZE;
	process->cycles -= 20;
}
