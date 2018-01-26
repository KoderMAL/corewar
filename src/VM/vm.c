/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 14:30:57 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/26 11:48:13 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "main/op.h"
#include <stdio.h> //A SUPPRIMER
static void vm_initialization(t_vm *vm, int ac)
{
	int i;

	i = 0;
	vm->nb_champs = ac - 1;
	vm->err_msg = NULL;
	while (i < MEM_SIZE)
		vm->map[i++] = 0;
	pqueue_init(&(vm->threads));
	thread_init(vm);
}

static void vm_clean(t_vm *vm, int fd[MAX_ARGS_NUMBER])
{
	int i;

	i = 0;
	err2_display(vm);
	pqueue_delete(&(vm->threads));
	while (i < MAX_ARGS_NUMBER)
		close(fd[i++]);
}

int main(int ac, char **av)
{
	t_vm vm;
	int fd[MAX_ARGS_NUMBER];
	int i;

	i = 0;
	vm.err = 0;
	if (ac - 1 > MAX_ARGS_NUMBER)
		err2(&vm, "Too many arguments");
	else if (ac < 2)
		err2(&vm, "Usage: ./corewar [champ.cor] [...] (4 files maximum)");
	printf("ac:%d-MAX%d\n", ac, MAX_ARGS_NUMBER);
	if (vm.err == 0)
	{
		vm_initialization(&vm, ac);
		while (i < vm.nb_champs)
			load_champion(&vm, av, &i, fd);
	}
	//fill map:
	printf("map\n");
	i = 0;
	while (i < MEM_SIZE)
	{
		printf("%0x ", vm.map[i++]);
		if (i % 64 == 0)
			printf("\n");
	}
/*	//HEXDUMP maison
	printf("hexdump\n");
	i = 0;
	while (i < MAX_SIZE)
	{
		printf("%x", vm.champs_fd[0].cor[i++]);
		if (i == (16 + PROG_NAME_LENGTH + COMMENT_LENGTH))
		{printf("\n*\n");}
		printf("-");
	}
	printf("\ni=%d\n", i);
	//HEXDUMP maison*/
	vm_clean(&vm, fd);
	return (0);
}