/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 14:31:43 by alalaoui          #+#    #+#             */
/*   Updated: 2018/02/12 16:17:33 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** this function returns 1 if there is no player with number n
*/

static int		is_number_available(t_vm *vm, int n)
{
	int	i;

	i = 0;
	while (i < vm->n_champs)
	{
		if (vm->champs[i].number == n)
			return (0);
		i++;
	}
	return (1);
}

/*
** this function finds the first available negative number
*/

static int		find_available_number(t_vm *vm)
{
	int	i;

	i = -1;
	while (1)
	{
		if (is_number_available(vm, i))
			return (i);
		i--;
	}
}

static void		add_champion(t_vm *vm, int n_is_set, int n, char *file_name)
{
	if (vm->n_champs >= MAX_PLAYERS)
		err2(vm, "too many champions (maximum is 4)");
	else if (ft_strlen(file_name) >= 4
			&& ft_strcmp(file_name + ft_strlen(file_name) - 4, ".cor") == 0)
	{
		if (n_is_set)
		{
			if (!is_number_available(vm, n))
				err2(vm, "too champions have the same number!");
		}
		else
			n = find_available_number(vm);
	}
	else
		err2(vm, file_name[0] == '-' ? "unknown option"
					: "file name must end with .cor");
	if (vm->err == 0)
	{
		champion_load(vm, &(vm->champs[vm->n_champs]), n, file_name);
		vm->n_champs++;
	}
}

int				parse_args(t_vm *vm, int ac, char **av)
{
	t_state state;
	int		n;
	int		n_is_set;
	int		i;

	n = 0;
	n_is_set = 0;
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
				add_champion(vm, n_is_set, n, av[i]);
				n_is_set = 0;
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
				n_is_set = 1;
				state = S_CHAMP;
			}
			else
				return (err2(vm, "-n option needs a number"));
		}
		else if (state == S_CHAMP)
		{
			add_champion(vm, n_is_set, n, av[i]);
			n_is_set = 0;
			state = S_START;
		}
		i++;
	}
	if (state != S_START)
		return (err2(vm, "syntax error in arguments"));
	return (0);
}
