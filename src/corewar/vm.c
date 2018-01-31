/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 14:30:57 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/31 15:00:42 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "mlx.h"
#include "vm.h"
#include "ft/ft.h"

void vm_init(t_vm *vm)
{
	int i;

	i = -1;
	vm->op = NULL;
	vm->err_msg = NULL;
	vm->game_cycle = 0;
	ft_memset(vm->map, 0, MEM_SIZE);
	while (++i < MAX_PLAYERS)
		ft_memset(&(vm->champs_fd[i]), 0, sizeof(t_champ));
}
void vm_start(t_vm *vm)
{
	vm->err = 0;
	vm->cycle_to_dump = -1;
	vm->v = 0;
	vm->d = 0;
	vm->n = 0;
	vm->draw_game = 0;
	vm->nb_champs = 0;
	ft_memset(vm->champ_n, -1, 4);
	pqueue_init(&(vm->threads));
	if (vm->draw_game)
		draw_game_init(vm);
}
void vm_clean(t_vm *vm)
{
	int i;

	i = 0;
	err2_display(vm);
	pqueue_delete(&(vm->threads));
	while (i < MAX_ARGS_NUMBER)
		close(vm->champs_fd[i++].file.fd);
	if (vm->draw_game)
		draw_game_clean(vm);
	exit(1);
}

static void check_exit(t_vm *vm)
{
	if (vm->cycle_to_dump != -1)
		vm->d = 2;
	else if (vm->draw_game == 1)
		vm->v = 1;
	if (vm->nb_champs == 0)
		err2(vm, "Usage : ./corewar [-d N | -visual] [[-n N] champ.cor] ...");
	if (vm->draw_game != 0 && vm->d != 0)
		err2(vm, "Please use either -d N dump or -visual option");
	if (vm->err)
	{
		err2_display(vm);
		exit(-1);
	}
}

int main(int ac, char **av)
{
	t_vm vm;
	int fd[MAX_ARGS_NUMBER];
	int i;

	i = 0;
	vm_start(&vm);
	ft_memset(fd, 0, MAX_ARGS_NUMBER);
	if (parse_args(&vm, ac, av) == 0)
		check_exit(&vm);
	check_exit(&vm);
	if (vm.err == 0)
		vm_init(&vm);
	if (vm.err == 0)
		while (i < vm.nb_champs && vm.err == 0)
			load_champion(&vm, av, &i, fd);
	if (vm.err == 0)
	{
		if (vm.draw_game)
			mlx_loop(vm.gui.mlx_ptr);
		else
			while (1)
				war_cycle(&vm);
	}
	vm_clean(&vm);
	return (0);
}
