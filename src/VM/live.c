/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lararamirez <lararamirez@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 11:32:35 by lramirez          #+#    #+#             */
/*   Updated: 2018/01/26 09:51:16 by lararamirez      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"

// Déplace le PC pour le placer sur le T_DIR à récupérer.
// Récupère le T_DIR sur 4 octets (int).
// Essaie de faire correspondre l'id récupéré avec un joueur - le cas échéant, print un live de ce joueur.
// Redéplace le PC à la suite du T_DIR.
// Décrémente le process de 10 cycles (coût d'un live).

void		live(t_vm *vm, t_thread process)
{
	int		id;

	process->location = (process->location + 4) % MEM_SIZE;
	id = map[process->location] << 24 | map[(process->location + 1) % MEM_SIZE] << 16 | map[(process->location + 2) % MEM_SIZE] << 8 | map[(process->location + 3) % MEM_SIZE];
	player = 0;
	while (player < vm->nbr_chmp)
	{
		if (id == vm->champs_fd[player]->id)
		{
			ft_printf("un processus dit que le joueur %d(%s) est en vie\n", player + 1, vm->champs_fd[player]->name);
			break;
		}
		player++;
	}
	process->location = (process->location + 4) % MEM_SIZE;
	process->cycles -= 10;
}
