/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 12:00:20 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/30 17:55:36 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/ft.h"
#include "vm.h"

void		dump(t_vm *vm)
{
	int		i;

	i = 0;
	if (vm->cycle_to_dump != -1)
	{
		if (vm->game_cycle == vm->cycle_to_dump)
		{
			while (i < MEM_SIZE)
			{
				printf("%x ", vm->map[i]);
				i++;
				if (i % 64 == 0)
					{printf("\n");}
			}
			exit(1);
		}
	}
}
