/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 14:30:57 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/17 18:53:05 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "main/op.h"

static void		vm_initialization(t_vm *vm, int ac)
{
	int			i;

	i = 0;
	vm->players = ac - 1;
	openfile_init();
	while(i < MEM_SIZE)
		vm->map[i++] = 0;
	thread_init(vm);
	
}

static void		vm_clean(t_vm *vm)
{
	err2_display(vm);
}

static void		read_champion(t_vm *vm, int i)
{
	int		ret;
	char	c;
	int		pos;

	pos = 0;
	while (vm->err == 0)
	{
		ret = openfile_read_char(&(vm->champs_fd[i].file), &c);
		if (ret = -1)
			err2(vm, "unable to read input");
		if (ret != 1)
			break ;
		vm->champs_fd[i].name[pos++] = c;
		if (pos > CHAMP_MAX_SIZE)
			err2(vm, "champion is too long");
		if (err == 1)
			return ;
	}
}

static void		load_champion(t_vm *vm, int ac, char *av, int *i)
{
	int			fd;

	fd = -1;
	if (env.err == 0 && (fd = open(av[*i], O_RDONLY)) < 2)
		err2(vm, "Unable to open input file");
	if (env.err == 0)
		openfile.init(&(vm.champs_fd[*i].file), fd);
	read_champion(vm, *i);
	*i++;
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
	vm_initialiszation(&vm, ac);
	while (i < MAX_PLAYERS)
		load_champion(vm, ac, av + i, &i);
	
	return (0);
}
