/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 11:51:36 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/29 10:20:44 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "gui/gui.h"
#include "gui/gui_hooks.h"

int	draw_game_init(t_vm *vm)
{
	gui_init(&(vm->gui), 1024, 768, "corewar");
	if (vm->gui.err == 1)
		return (err2(vm, vm->gui.err_msg));
	gui_init_hooks(vm);
	return (0);
}

void		draw_game(t_vm *vm)
{
	(void)vm;
}

void		draw_game_clean(t_vm *vm)
{
	gui_clean(&(vm->gui));
	if (vm->gui.err)
		err2(vm, vm->gui.err_msg);
}
