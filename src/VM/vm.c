/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 14:30:57 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/17 15:43:11 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "main/op.h"

static void		vm_initialization(t_vm *vm)
{
	int			i;

	i = 0;
	vm->players = ac - 1;
	openfile_init();
	while(i < MEM_SIZE)
		vm->map[i++] = 0;
	thread_init(vm);
	
}

/*
static void		read_champion(t_vm *vm)
{
	int		ret;
	char	c;

	while (vm->err == 0)
	{
		ret = openfile_read_char($(vm->input), &c);
		if (ret = -1)
			err2(vm, "unable to read input");
		if (ret != 1)
			break ;
		parse_champion(vm, c);
	}
}*/

static void		load_champion(t_vm *vm, int ac, char *av)
{
	int			fd;

	fd = -1;
	if (env.err == 0 && (fd = open(av[i], O_RDONLY)) < 2)
		err2(vm, "Unable to open input file");
	if (env.err == 0;)
	openfile.init(&(env.input), fd);
	
}

int		main(int ac, char **av)
{
	t_vm	vm;
	int		fd[MAX_ARGS_NUMBER];
	int		i;

	i = 0;
	if (ac > MAX_ARGS_NUMBER)
		err2(vm, "Too many arguments");
	else if (ac < 2)
		err2(vm, "Usage: ./corewar [champ.cor] [...] (4 files maximum)")
	vm_initialiszation(&vm);
	while (i < MAX_ARGS_NUMBER)
		load_champion(vm, ac, av + i++);
			
	return (0);
}
