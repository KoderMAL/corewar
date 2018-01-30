/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 14:30:57 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/30 18:13:51 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "mlx.h"
#include "vm.h"
#include "ft/ft.h"

void vm_init(t_vm *vm)
{
	int i;

	i = 0;
	vm->op = NULL;
	vm->err_msg = NULL;
	vm->game_cycle = 0;
	vm->cycle_to_dump = -1;
	ft_memset(vm->map, 0, MEM_SIZE);
	pqueue_init(&(vm->threads));
}
void vm_start(t_vm *vm)
{
	vm->err = 0;
	vm->v = 0;
	vm->d = 0;
	vm->draw_game = 0;
	vm->nb_champs = 0;
	ft_memset(vm->champ_n, 0, 4);
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

static void check_exit(t_vm *vm, int ac)
{
	if (vm->nb_champs == 0)
		err2(vm, "Usage : ./corewar [-d N | -visual] [[-n N] champ.cor] ...");
	if (vm->err)
	{
		err2_display(vm);
		exit(-1);
	}
	if (vm->cycle_to_dump != -1)
		vm->d = 2;
	else if (vm->draw_game == 1)
		vm->v = 1;
}

int main(int ac, char **av)
{
	t_vm vm;
	int fd[MAX_ARGS_NUMBER];
	int i;

	i = 0;
	vm_start(&vm);
	if (parse_args(&vm, ac, av) == 0)
		check_exit(&vm, ac);
	if (vm.err == 0)
		vm_init(&vm);
	if (vm.err == 0)
		while (i < vm.nb_champs && vm.err == 0)
			load_champion(&vm, av, &i, fd);
	printf("\nERR=%d\n", vm.err);
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
