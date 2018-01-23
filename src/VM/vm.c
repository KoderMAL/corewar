/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 14:30:57 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/23 14:01:58 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "main/op.h"
#include <stdio.h> //A SUPPRIMER
static void vm_initialization(t_vm *vm, int ac /*,int fd[4]*/)
{
	int i;

	i = 0;
	vm->nb_champs = ac - 1;
//	openfile_init(&vm->champs_fd[0].file, fd[0]);
	pqueue_init(&(vm->threads));
	while (i < MEM_SIZE)
		vm->map[i++] = 0;
	thread_init(vm);
}

static void vm_clean(t_vm *vm, int fd[MAX_ARGS_NUMBER])
{
	int i;

	i = 0;
	err2_display(vm);
	while (i < MAX_ARGS_NUMBER)
		close(fd[i++]);
}

static void read_champion(t_vm *vm, int i)
{
	int ret;
	char c;
	int pos;

	pos = 0;
	while (vm->err == 0)
	{
		printf("check\n");
		ret = openfile_read_char(&(vm->champs_fd[i].file), &c);
		if (ret == -1)
			err2(vm, "unable to read input");
		if (ret != 1)
			break;
		vm->champs_fd[i].name[pos++] = c;
		if (pos > CHAMP_MAX_SIZE)
			err2(vm, "champion is too long");
		if (vm->err == 1)
			return;
	}
}

static void load_champion(t_vm *vm, char **av, int *i, int fd[MAX_ARGS_NUMBER])
{
	if (vm->err == 0 && (fd[*i] = open(av[(*i) + 1], O_RDONLY)) < 2)
		err2(vm, "Unable to open input file");
	if (vm->err == 0)
		openfile_init(&(vm->champs_fd[*i].file), fd[*i]);
	read_champion(vm, *i);
	(*i)++;
}

int main(int ac, char **av)
{
	t_vm vm;
	int fd[MAX_ARGS_NUMBER];
	int i;

	i = 0;
	if (ac > MAX_ARGS_NUMBER)
		err2(&vm, "Too many arguments");
	else if (ac < 2)
		err2(&vm, "Usage: ./corewar [champ.cor] [...] (4 files maximum)");
/*	while (i < MAX_ARGS_NUMBER)
	{
		if (vm.err == 0 && (fd[i] = open(av + 1 + i, O_RDONLY) < 2)
			err2(&vm, "Unable to open an input file", 1);
	}
	i = 0;*/
	if (vm.err)
	{
		vm_initialization(&vm, ac);
		while (i < MAX_PLAYERS)
			load_champion(&vm, av, &i, fd);
	}
	vm_clean(&vm, fd);
	return (0);
}