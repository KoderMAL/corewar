/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 11:32:35 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/24 19:17:14 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** L’instruction qui permet à un processus de rester vivant. A également pour
** effet de rapporter que le joueur dont le numéro est en paramètre est en vie.
** Oh, et son seul paramètre est sur 4 octets.
*/

void		op_live(t_thread *pc)
{
	int				id;
	t_champ			*player;
	char			*player_itoa;
	int				i;

	pc->alive = true;
	id = get(pc, 0, false);
	player_itoa = ft_itoa(id + 1);
	i = 0;
	while (i < pc->vm->n_champs)
	{
		player = &(pc->vm->champs[i]);
		if (id == player->number)
		{
			pc->vm->num_lives++;
			player->last_live = pc->vm->game_cycle;
			// write(1, "un processus dit que le joueur ", 31);
			// write(1, player_itoa, ft_strlen(player_itoa));
			// write(1, "(", 1);
			// write(1, pc->vm->champs[player].name,
			// 	ft_strlen(pc->vm->champs[player].name));
			// write(1, ") est en vie\n", 13);
			break ;
		}
		i++;
	}
}
