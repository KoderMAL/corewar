/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 14:31:43 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/31 11:58:29 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		add_champion(t_vm *vm, int n, char *av)
{
	if (ft_strlen(av) > 4)
	{
		if (av[ft_strlen(av) - 1] == 'r' && av[ft_strlen(av) - 2] == 'o' && av[ft_strlen(av) - 3] == 'c' && av[ft_strlen(av) - 4] == '.')
			vm->nb_champs++;
		else
			err2(vm, "invalid input file");
		if (n != -1)
			vm->champ_n[vm->nb_champs - 1] = n;
	}
	else
		err2(vm, "invalid file input");
}

int				check_option(t_vm *vm, char **av, int i)
{
	printf("champ_n[i]:%d\n", vm->champ_n[i]);
	if (vm->champ_n[i] != -1)
		return (2);
	else
		return (0);
}

int 			parse_args(t_vm *vm, int ac, char **av)
{
	t_state state;
	int 	n;
	int 	i;
	int 	c;

	c = 0;
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
				state= S_N;
			else
			{
				add_champion(vm, n, av[i]);
				vm->champ_n[c++] = n;
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
				vm->champ_n[c++] = n;
				n = -1;
				state = S_START;
		}
		i++;
	}
	if (state != S_START)
		return (err2(vm, "syntax error in arguments"));
	return (0);
}