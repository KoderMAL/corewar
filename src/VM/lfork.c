/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 11:18:58 by lramirez          #+#    #+#             */
/*   Updated: 2018/01/26 12:04:13 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"

// Déplace le PC pour le placer sur le T_DIR à récupérer.
// Récupère le T_DIR sur 2 octets (short).
// Crée un nouveau process à l'index récupéré.
// Déplace le PC du process d'origine à la fin du short récupéré.
// Décrémente le process d'origine de 1000 cycles (coût d'un lfork).

void		lfork(t_vm *vm, t_thread process)
{
	short	index;

	process->location = (process->location + 4) % MEM_SIZE;
	index = map[process->location] << 8 | map[(process->location + 1) % MEM_SIZE];
	pqueue_push(vm->threads, dup_thread(process, (process->location + index) % MEM_SIZE));
	process->location = (process->location + 2) % MEM_SIZE;
	process->cycles -= 1000;
}
