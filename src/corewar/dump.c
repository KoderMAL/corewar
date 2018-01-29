/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 12:00:20 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/29 14:53:50 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/ft.h"
#include "vm.h"

void		parse_options(t_vm *vm, int *ac, char **av)
{
	if (ft_strcmp(av[1], "-visual") == 0)
	{
		if (*ac < 3)
			exit(-1);
		vm->draw_game = 1;
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
	{
		vm->option[0] = 0;
		vm->draw_game = 0;
	}
	/*
	**if (OPTION -N)
	**{
	**	CODER OPTION -n
	}*/
}

int			parse_number(t_vm *vm, char **av, int *i)
{
	int		n;

	n = 0;
	if (vm->draw_game == 1)
	{
		if (ft_strcmp(av[*i + 2], "-n") == 0 && ft_str_isdigit(av[*i + 3]))
		{
			n = ft_atoi(av[*i + 3]);
			(*i)++;
		}
	}
	else
	{
		if (ft_strcmp(av[*i + (vm->option[0] * 2 ) + 1], "-n") == 0 &&
		ft_str_isdigit(av[*i + (vm->option[0] * 2 ) + 2]))
		{
			n = ft_atoi(av[*i + (vm->option[0] * 2 ) + 2]);
			(*i)++;
		}
	}
	return (n);
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
