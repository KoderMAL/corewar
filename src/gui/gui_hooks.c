/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 09:49:04 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/29 10:16:18 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mlx.h"
# include "gui.h"
# include "font.h"
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

int		gui_redraw(t_vm *vm)
{
	t_font_cursor	fc;

	font_cursor_init(&fc, vm->gui.font, (t_coord){100, 100}, 5);
	font_cursor_print(&(vm->gui), &fc, "BLABLA BLA");
	font_cursor_print(&(vm->gui), &fc, "\n");	
	font_cursor_print(&(vm->gui), &fc, "TRUCMUCHE 1337");
	mlx_put_image_to_window(vm->gui.mlx_ptr, vm->gui.mlx_win, vm->gui.image_ptr, 0, 0);
	clear_image(vm->gui.image, vm->gui.screen_size, (t_pix)(unsigned int)0);
	return (0);
}

void		gui_init_hooks(t_vm *vm)
{
	mlx_hook(vm->gui.mlx_win, 17, 0, &gui_close, vm);
	mlx_key_hook(vm->gui.mlx_win, &gui_key_pressed, vm);
	mlx_loop_hook(vm->gui.mlx_ptr, &gui_redraw, vm);
}
