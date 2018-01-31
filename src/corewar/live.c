/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 11:32:35 by lramirez          #+#    #+#             */
/*   Updated: 2018/01/28 17:54:50 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

// Déplace le PC pour le placer sur le T_DIR à récupérer.
// Récupère le T_DIR sur 4 octets.
// Essaie de faire correspondre l'id récupéré avec un joueur - le cas échéant, print un live de ce joueur.
// Déplace le PC à la suite du T_DIR récupéré.
// Décrémente le process de 10 cycles (coût d'un live).

void		op_live(t_vm *vm, t_thread *process)
{
	int		id;
	int		player;

	process->location = (process->location + 1) % MEM_SIZE;
	printf("premier octet: %d\n", vm->map[process->location]);
	printf("deuxieme octet: %d\n", vm->map[(process->location + 1) % MEM_SIZE]);
	printf("troisieme octet: %d\n", vm->map[(process->location + 2) % MEM_SIZE]);
	printf("quatrieme octet: %d\n", vm->map[(process->location+ 3) % MEM_SIZE]);
id = vm->map[process->location] << 24 | vm->map[(process->location + 1) % MEM_SIZE] << 16 | vm->map[(process->location + 2) % MEM_SIZE] << 8 | vm->map[(process->location + 3) % MEM_SIZE];
	printf("champion id:%d\n", id);
	player = 0;
	while (player < vm->nb_champs)
	{
		if (id == vm->champs_fd[player].id)
		{
			// noter que tel joueur a fait un live a tel cycle dans champ
			printf("un processus dit que le joueur %d(%s) est en vie\n", player + 1, vm->champs_fd[player].name);
			break;
		}
		player++;
	}
	process->location = (process->location + 4) % MEM_SIZE;
	process->cycles -= 10;
}