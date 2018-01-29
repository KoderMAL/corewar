/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 11:51:36 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/29 11:55:20 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "vm.h"
# include "gui/font.h"
#include "gui/gui.h"
#include "gui/gui_corewar.h"

int	draw_game_init(t_vm *vm)
{
	gui_init(&(vm->gui), 1024, 768, "corewar");
	if (vm->gui.err == 1)
		return (err2(vm, vm->gui.err_msg));
	fonts_load(vm);
	if (vm->gui.err == 1)
		return (err2(vm, vm->gui.err_msg));
	gui_init_hooks(vm);
	return (0);
}

void		draw_game_loop(t_vm *vm)
{
	t_font_cursor	fc;

	war_cycle(vm);
	clear_image(vm->gui.image, vm->gui.screen_size, (t_pix)(unsigned int)0);
	font_cursor_init(&fc, &(vm->fonts[2]), (t_coord){100, 100}, 5);
	font_cursor_print(&(vm->gui), &fc, "COREWAR\n");
	fc.font = &(vm->fonts[1]);
	font_cursor_print(&(vm->gui), &fc, "ALALAOUI\n");
	font_cursor_print(&(vm->gui), &fc, "DHADLEY\n");
	font_cursor_print(&(vm->gui), &fc, "LRAMIREZ\n");
	font_cursor_print(&(vm->gui), &fc, "STOUPIN\n");
	mlx_put_image_to_window(vm->gui.mlx_ptr, vm->gui.mlx_win, vm->gui.image_ptr, 0, 0);
}

void		draw_game_clean(t_vm *vm)
{
	gui_clean(&(vm->gui));
	fonts_clean(vm);
	if (vm->gui.err)
		err2(vm, vm->gui.err_msg);
}
