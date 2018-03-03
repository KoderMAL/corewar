/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 11:32:35 by lramirez          #+#    #+#             */
/*   Updated: 2018/03/03 14:50:25 by stoupin          ###   ########.fr       */
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
	int				i;

	id = get(pc, 0, false);
	i = 0;
	while (i < pc->vm->n_champs)
	{
		player = &(pc->vm->champs[i]);
		if (id == player->number)
		{
			player->last_live = pc->vm->game_cycle;
			pc->vm->played_last = i;
			print_str(pc->vm, "\nPlayer ", 0);
			print_nbr(pc->vm, i + 1, 0);
			print_str(pc->vm, " (", 0);
			print_str(pc->vm, player->name, 0);
			print_str(pc->vm, ") is said to be alive", 0);
			break ;
		}
		i++;
	}
	pc->vm->num_lives++;
	pc->last_live = pc->vm->game_cycle;
	pc->alive = true;
}
