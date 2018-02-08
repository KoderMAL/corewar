/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 14:31:43 by alalaoui          #+#    #+#             */
/*   Updated: 2018/02/08 18:41:42 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int		find_available_slot(t_vm *vm)
{
	int	i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->champs[i].loaded == 0)
			return (i);
		i++;
	}
	return (-1);
}

static void		add_champion(t_vm *vm, int n, char *file_name)
{
	if (vm->n_champs >= MAX_PLAYERS)
		err2(vm, "too many champions (maximum is 4)");
	else if (ft_strlen(file_name) >= 4
			&& ft_strcmp(file_name + ft_strlen(file_name) - 4, ".cor") == 0)
	{
		if (n == -1)
			n = find_available_slot(vm);
		champion_load(vm, &(vm->champs[n]), file_name);
		vm->n_champs++;
	}
	else
		err2(vm, "file name must end with .cor");
}

int				parse_args(t_vm *vm, int ac, char **av)
{
	t_state state;
	int		n;
	int		i;

	n = -1;
	i = 1;
	state = S_START;
	while (i < ac && vm->err == 0)
	{
		if (state == S_START)
		{
			if (ft_strcmp(av[i], "-d") == 0)
				state = S_D;
			else if (ft_strcmp(av[i], "-visual") == 0)
				vm->draw_game = 1;
			else if (ft_strcmp(av[i], "-n") == 0)
				state = S_N;
			else
			{
				add_champion(vm, n, av[i]);
				n = -1;
			}
		}
		else if (state == S_D)
		{
			if (ft_str_isdigit(av[i]))
			{
				if ((vm->cycle_to_dump = ft_atoi(av[i])) < 0)
					err2(vm, "Negative dump (I cant send you back in time)");
				state = S_START;
			}
			else
				return (err2(vm, "-d option needs a number"));
		}
		else if (state == S_N)
		{
			if (ft_str_isdigit(av[i]))
			{
				n = ft_atoi(av[i]);
				state = S_CHAMP;
			}
			else
				return (err2(vm, "-n option needs a number"));
		}
		else if (state == S_CHAMP)
		{
			add_champion(vm, n, av[i]);
			n = -1;
			state = S_START;
		}
		i++;
	}
	if (state != S_START)
		return (err2(vm, "syntax error in arguments"));
	return (0);
}
