/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 12:00:20 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/29 12:03:05 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/ft.h"
#include "vm.h"

void		parse_options(t_vm *vm, int *ac, char **av)
{
		vm->draw_game = 0;
	if (ft_strcmp(av[1], "-visual") == 0)
	{
		if (*ac < 3)
			exit(-1);
		vm->draw_game = 0;
		*ac = *ac - 1;
		return ;
	}
	else if (ft_strcmp(av[1], "-d") == 0 && ft_str_isdigit(av[2]))
	{
		if ((*ac) < 4)
			exit(-1);
		vm->option[0] = 1;
		vm->option[1] = ft_atoi(av[2]);
		if (vm->option[1] < 0)
			err2(vm, "negative dump spotted");
		*ac = *ac - 2;
	}
	else
		vm->option[0] = 0;
	/*if (OPTION -N)
	{
		CODER OPTION -n
	}*/
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
				printf("%x ", vm->map[i]);
				i++;
				if (i % 64 == 0)
					{printf("\n");}
			}
			exit(1);
		}
	}
}
