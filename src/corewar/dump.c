/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 12:00:20 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/31 12:11:09 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/ft.h"
#include "vm.h"

static void	write_map(t_vm *vm)
{
	char				converted[MEM_SIZE * 3 + MEM_SIZE / 32 + 1];
	unsigned char		byte;
	static const char	digits[16] = "0123456789ABCDEF";
	int					i;
	int					j;

	i = 0;
	j = 0;
	while (i < MEM_SIZE * 3)
	{
		byte = vm->map[i];
		converted[j] = digits[byte / 16];
		converted[j + 1] = digit[byte % 16]
		j += 2;
		if (j % 64 == 0)
			converted[j] = '\n';
		else
			converted[j] = ' ';
		j++;
		i++;
	}
	write(1, converted, MEM_SIZE * 3);
}

void		dump(t_vm *vm)
{
	int		i;

	i = 0;
	if (vm->cycle_to_dump != -1)
	{
		if (vm->game_cycle == vm->cycle_to_dump)
		{
			write_map(vm);
		}
			exit(1);
		}
	}
}
