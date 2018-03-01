/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 15:11:08 by alalaoui          #+#    #+#             */
/*   Updated: 2018/03/01 16:55:33 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void state_start(t_vm *vm, char *av)
{
	if (ft_strcmp(av, "-d") == 0)
		vm->state = &state_d;
	else if (ft_strcmp(av, "-visual") == 0)
		vm->draw_game = 1;
	else if (ft_strcmp(av, "-verbose") == 0)
		vm->verbose = 1;
	else if (ft_strcmp(av, "-zaz") == 0)
		vm->zaz_mode = 1;
	else if (ft_strcmp(av, "-n") == 0)
		vm->state = &state_n;
	else if (ft_strcmp(av, "-s") == 0)
		vm->state = &state_s;
	else
	{
		add_champion(vm, vm->n_is_set, vm->n, av);
		vm->n_is_set = 0;
	}
}

void state_champ(t_vm *vm, char *av)
{
	add_champion(vm, vm->n_is_set, vm->n, av);
	vm->n_is_set = 0;
	vm->state = &state_start;
}

void state_s(t_vm *vm, char *av)
{
	if (ft_str_isdigit(av))
	{
		vm->dump_every = ft_atoi(av);
		vm->state = &state_start;
	}
	else
		err2(vm, "-s option needs a number");
}

void state_n(t_vm *vm, char *av)
{
	if (ft_str_isdigit(av))
	{
		vm->n = ft_atoi(av);
		vm->n_is_set = 1;
		vm->state = &state_champ;
	}
	else
		err2(vm, "-n option needs a number");
}

void state_d(t_vm *vm, char *av)
{
	if (ft_str_isdigit(av))
	{
		if ((vm->cycle_to_dump = ft_atoi(av)) < 0)
			err2(vm, "Negative dump (I cant send you back in time)");
		vm->state = &state_start;
	}
	else
		err2(vm, "-d option needs a number");
}