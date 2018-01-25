/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 17:58:09 by lramirez          #+#    #+#             */
/*   Updated: 2018/01/25 17:58:29 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"

void		zjmp(t_vm *vm, t_thread process)
{
	char	move;
	int		id;

	move = 4;
	while (move)
	{
		if (process->location == MEM_SIZE - 1)
			process->location = 0;
		(process->location)++;
		move--;
	}
	id = map[process->location] << 24 | map[process->location + 1] << 16 | map[process->location + 2] << 8 | map[process->location + 3];
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
	move = 4;
	while (move)
	{
		if (process->location == MEM_SIZE - 1)
			process->location = 0;
		(process->location)++;
		move--;
	}
	process->cycles -= 10;
}
