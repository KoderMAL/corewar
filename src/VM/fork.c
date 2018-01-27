/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 11:24:05 by lramirez          #+#    #+#             */
/*   Updated: 2018/01/27 11:44:56 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"

// Déplace le PC pour le placer sur le T_DIR à récupérer.
// Récupère le T_DIR sur 2 octets.
// Crée un nouveau process à l'index récupéré (avec % IDX_MOD).
// Déplace le PC du process d'origine à la fin du T_DIR récupéré.
// Décrémente le process d'origine de 800 cycles (coût d'un fork).

void		op_fork(t_vm *vm, t_thread process)
{
	short	index;

	process->location = (process->location + 1) % MEM_SIZE;
	index = vm->map[process->location] << 8 | vm->map[(process->location + 1) % MEM_SIZE];
	pqueue_push(vm->threads, dup_thread(process, (process->location + (index % IDX_MOD)) % MEM_SIZE));
	process->location = (process->location + 2) % MEM_SIZE;
	process->cycles -= 800;
}
