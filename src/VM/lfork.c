/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 11:18:58 by lramirez          #+#    #+#             */
/*   Updated: 2018/01/28 16:48:23 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"

// Déplace le PC pour le placer sur le T_DIR à récupérer.
// Récupère le T_DIR sur 2 octets.
// Crée un nouveau process à l'index récupéré (sans % IDX_MOD).
// Déplace le PC du process d'origine à la fin du T_DIR récupéré.
// Décrémente le process d'origine de 1000 cycles (coût d'un lfork).

void		op_lfork(t_vm *vm, t_thread process)
{
	short	index;

	process->location = (process->location + 1) % MEM_SIZE;
	index = vm->map[process->location] << 8 | vm->map[(process->location + 1) % MEM_SIZE];
	pqueue_push(&(vm->threads), dup_thread(process, (process->location + index) % MEM_SIZE));
	process->location = (process->location + 2) % MEM_SIZE;
	process->cycles -= 1000;
}
