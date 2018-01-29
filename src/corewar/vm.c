/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 14:30:57 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/29 14:04:10 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "mlx.h"
#include "vm.h"
#include "asm/op.h"

void	vm_init(t_vm *vm, int ac)
{
	int i;

	i = 0;
	vm->nb_champs = ac - 1;
	vm->op = NULL;
	vm->err_msg = NULL;
	vm->game_cycle = 0;
	while (i < MEM_SIZE)
		vm->map[i++] = 0;
	pqueue_init(&(vm->threads));
	thread_init(vm);
	if (vm->draw_game)
		draw_game_init(vm);
}

void	vm_clean(t_vm *vm)
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

int		main(int ac, char **av)
{
	t_vm	vm;
	int		fd[MAX_ARGS_NUMBER];
	int		i;

	i = 0;
	vm.err = 0;
	vm.draw_game = 0;
	if (ac - 1 > MAX_ARGS_NUMBER)
		err2(&vm, "Too many arguments");
	else if (ac < 2)
		err2(&vm, "Usage: ./corewar [-d N] [-visual] [[-n N]champ.cor] ...");
	else if (vm.err == 0)
		parse_options(&vm, &ac, av);
	if (vm.err == 0)
		vm_init(&vm, ac);
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
