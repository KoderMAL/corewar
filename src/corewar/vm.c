/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 14:30:57 by alalaoui          #+#    #+#             */
/*   Updated: 2018/02/12 17:13:13 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "mlx.h"
#include "vm.h"
#include "ft/ft.h"

void		vm_init(t_vm *vm)
{
	ft_memset(vm, 0, sizeof(*vm));
	openfile_init(&(vm->stdout), STDOUT_FILENO);
	openfile_init(&(vm->stderr), STDERR_FILENO);
	vm->cycle_to_dump = -1;
	vm->cycle_to_die = 0;
	vm->num_checkups = 0;
	vm->num_lives = 0;
}

void		vm_start(t_vm *vm)
{
	int	i;

	pqueue_init(&(vm->threads));
	i = 0;
	while (i < vm->n_champs)
	{
		pqueue_push(&(vm->threads), create_thread(vm, i));
		i++;
	}
	if (vm->draw_game)
		draw_game_init(vm);
}

void		vm_clean(t_vm *vm)
{
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
	if (vm.err == 0)
	{
		openfile_write_str(&(vm.stdout), "Introducing contestants...", 1);
		i = 0;
		while (i < vm.n_champs && vm.err == 0)
		{
			openfile_write_str(&(vm.stdout), "* Player ", 0);
			openfile_write_nbr(&(vm.stdout), i + 1, 0);
			openfile_write_str(&(vm.stdout), ", weighing ", 0);
			openfile_write_nbr(&(vm.stdout), vm.champs[i].size_bytecode, 0);
			openfile_write_str(&(vm.stdout), " bytes, \"", 0);
			openfile_write_str(&(vm.stdout), vm.champs[i].name, 0);
			openfile_write_str(&(vm.stdout), "\" (\"", 0);
			openfile_write_str(&(vm.stdout), vm.champs[i].comment, 0);
			openfile_write_str(&(vm.stdout), "\") !", 1);
			champion_to_vm(&vm, i);
			i++;
		}
		vm_start(&vm);
	}
	if (vm.err == 0)
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
