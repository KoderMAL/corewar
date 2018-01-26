/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 12:00:20 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/26 14:32:42 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		parse_options(t_vm *vm, int *ac, char **av)
{
	if (ft_strcmp(av[1], "-d") == 0 && ft_str_isdigit(av[2]))
	{
		vm->option[0] = 1;
		vm->option[1] = ft_atoi(av[2]);
		*ac = *ac - 2;
	}
	else
		vm->option[0] = 0;
	if (OPTION -N)
}

void		dump(t_vm *vm)
{
	int		i;

	i = 0;
	if (vm->option[0] == 1)
	{
		if (vm->game_cycle == vm->option[1])
		{
			while (i < MEM_SIZE)
			{
				printf("%x ", vm->map[i++]);
				if (i % 64 == 0)
					write(1, "\n", 1);
			}
			exit(0);
		}
	}
}