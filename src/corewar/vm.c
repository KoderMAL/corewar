/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 14:30:57 by alalaoui          #+#    #+#             */
/*   Updated: 2018/02/21 16:45:08 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "mlx.h"
#include "vm.h"
#include "ft/ft.h"
#define USAGE "Usage: ./corewar [-verbose] [-visual] [-d N] [[-n N] champ.cor]"

void		vm_init(t_vm *vm)
{
	ft_memset(vm, 0, sizeof(*vm));
	openfile_init(&(vm->stdout), STDOUT_FILENO);
	openfile_init(&(vm->stderr), STDERR_FILENO);
	vm->cycle_to_dump = -1;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->num_checkups = 0;
	vm->num_lives = 0;
}

void		vm_start(t_vm *vm)
{
	int			i;
	t_thread	*thread;

	pqueue_init(&(vm->threads));
	i = 0;
	while (i < vm->n_champs)
	{
		thread = create_thread(vm, vm->champs[i].number);
		if (thread)
			pqueue_push(&(vm->threads), thread);
		else
		{
			err2(vm, "memory error");
			break ;
		}
		i++;
	}
	if (vm->draw_game)
		draw_game_init(vm);
	vm->winner = 0;
}

void		vm_clean(t_vm *vm)
{
	if (vm->err == 0)
	{
		if (vm->n_champs < 1)
			err2(vm, "need at least one champion");
	}
	err2_display(vm);
	pqueue_delete(&(vm->threads));
	if (vm->draw_game)
		draw_game_clean(vm);
	openfile_flush(&(vm->stdout));
	openfile_flush(&(vm->stderr));
	exit(vm->err);
}

int			main(int argc, char **argv)
{
	t_vm	vm;
	int		i;

	vm_init(&vm);
	parse_args(&vm, argc, argv);
	if (argc < 2)
		err2(&vm, USAGE);
	if (vm.err == 0 && vm.n_champs > 0)
	{
		openfile_write_str(&(vm.stdout), "Introducing contestants...", 1);
		i = 0;
		while (i < vm.n_champs && vm.err == 0)
			announce_war(&vm, i++);
		vm_start(&vm);
	}
	if (vm.err == 0 && vm.n_champs > 0)
	{
		if (vm.draw_game)
			mlx_loop(vm.gui.mlx_ptr);
		else
			while (1)
				war_cycle(&vm);
	}
	vm_clean(&vm);
	return (vm.err);
}
