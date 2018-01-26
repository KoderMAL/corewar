/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 14:30:57 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/26 16:56:22 by alalaoui         ###   ########.fr       */
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
	vm->game_cycle = 0;
	while (i < MEM_SIZE)
		vm->map[i++] = 0;
	pqueue_init(&(vm->threads));
	thread_init(vm);
	draw_game_init(vm);
}

static void vm_clean(t_vm *vm, int fd[MAX_ARGS_NUMBER])
{
	int i;

	i = 0;
	err2_display(vm);
	pqueue_delete(&(vm->threads));
	while (i < MAX_ARGS_NUMBER)
		close(fd[i++]);
	draw_game_clean(vm);
}

int main(int ac, char **av)
{
	t_vm vm;
	int fd[MAX_ARGS_NUMBER];
	int i;

	i = 0;
	vm.err = 0;
	parse_options(&vm, &ac, av);
	if (ac - 1 > MAX_ARGS_NUMBER)
		err2(&vm, "Too many arguments");
	else if (ac < 2)
		err2(&vm, "Usage: ./corewar [-d N] [[-n N]champ.cor] ...)");
	if (vm.err == 0)
	{
		vm_initialization(&vm, ac);
		while (i < vm.nb_champs)
			load_champion(&vm, av, &i, fd);
	}
	war(&vm);
	vm_clean(&vm, fd);
	return (0);
}