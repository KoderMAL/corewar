/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 09:49:04 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/29 11:10:11 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mlx.h"
# include "corewar/vm.h"

int		gui_close(t_vm *vm)
{
	vm_clean(vm);
	exit(vm->err);
	return (0);
}

int		gui_key_pressed(int key, t_vm *vm)
{
	if (key == KEY_ESC)
		gui_close(vm);
	return (0);
}

void		gui_init_hooks(t_vm *vm)
{
	mlx_hook(vm->gui.mlx_win, 17, 0, &gui_close, vm);
	mlx_key_hook(vm->gui.mlx_win, &gui_key_pressed, vm);
	mlx_loop_hook(vm->gui.mlx_ptr, &draw_game_loop, vm);
}
