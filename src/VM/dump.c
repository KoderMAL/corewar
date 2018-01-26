/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 12:00:20 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/26 12:28:57 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		parse_options(t_vm *vm, int ac, char **av)
{
	if (ft_strcmp(av[1], "-d") == 0 && ft_str_isdigit(av[2]))
	{
		vm->option[0] = 1;
		vm->option[1] = ft_atoi(av[2]);
	}
	if
}

void		dump(t_vm *vm)
{
	if (vm->option[0] = 1)
}