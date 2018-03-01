/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 14:31:43 by alalaoui          #+#    #+#             */
/*   Updated: 2018/03/01 17:00:54 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** this function returns 1 if there is no player with number n
*/

int		is_number_available(t_vm *vm, int n)
{
	int i;

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

int		find_available_number(t_vm *vm)
{
	int i;

	i = -1;
	while (1)
	{
		if (is_number_available(vm, i))
			return (i);
		i--;
	}
}

void	add_champion(t_vm *vm, int n_is_set, int n, char *file_name)
{
	if (vm->n_champs >= MAX_PLAYERS)
		err2(vm, "too many champions (maximum is 4)");
	else if (ft_strlen(file_name) >= 4 &&
	ft_strcmp(file_name + ft_strlen(file_name) - 4, ".cor") == 0)
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

int		parse_args(t_vm *vm, int ac, char **av)
{
	int i;

	i = 1;
	vm->n = 0;
	vm->n_is_set = 0;
	vm->state = &state_start;
	while (i < ac && vm->err == 0)
	{
		(vm->state)(vm, av[i]);
		if (vm->err)
			return (vm->err);
		i++;
	}
	if (vm->state != &state_start)
		return (err2(vm, "syntax error in arguments"));
	return (0);
}
