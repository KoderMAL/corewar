/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 11:32:35 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/17 15:08:17 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		op_live(t_thread *pc)
{
	int		id;
	int		player;
	char	*player_itoa;

	pc->alive = true;
	id = get(pc, 0);
	player_itoa = ft_itoa(id + 1);
	player = 0;
	while (player < pc->vm->n_champs)
	{
		if (id == player)
		{
			pc->vm->num_lives++;
			pc->vm->champs[player].last_live = pc->vm->game_cycle;
			write(1, "un processus dit que le joueur ", 31);
			write(1, player_itoa, ft_strlen(player_itoa));
			write(1, "(", 1);
			write(1, pc->vm->champs[player].name,
				ft_strlen(pc->vm->champs[player].name));
			write(1, ") est en vie\n", 13);
			break ;
		}
		player++;
	}
}
