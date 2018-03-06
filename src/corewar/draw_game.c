/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 11:51:36 by alalaoui          #+#    #+#             */
/*   Updated: 2018/02/25 14:58:18 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "vm.h"
#include "gui/font.h"
#include "gui/gui.h"
#include "gui/gui_corewar.h"

int		draw_game_init(t_vm *vm)
{
	gui_init(&(vm->gui), 2400, 1080, "corewar");
	if (vm->gui.err == 1)
		return (err2(vm, vm->gui.err_msg));
	fonts_load(vm);
	if (vm->gui.err == 1)
		return (err2(vm, vm->gui.err_msg));
	gui_init_hooks(vm);
	return (0);
}

void	draw_map(t_vm *vm, t_font_cursor *fc)
{
	char				line[130];
	t_coord				c;
	unsigned char		byte;
	static const char	digits[16] = "0123456789ABCDEF";

	c.y = -1;
	while (++c.y < 64)
	{
		c.x = -1;
		while (++c.x < 64)
		{
			byte = vm->map[c.y * 64 + c.x];
			line[2 * c.x] = digits[byte / 16];
			line[2 * c.x + 1] = digits[byte % 16];
		}
		line[128] = '\n';
		line[129] = '\0';
		font_cursor_print(&(vm->gui), fc, line);
	}
}

void	draw_processes(t_vm *vm, t_coord c0, t_font *f)
{
    t_pqueue_elem	*elem;
	t_thread		*pc;
	int				i;
	t_coord			c;
	int				location;
	
	elem = vm->threads.first;
	while (elem)
	{
		pc = (t_thread*)elem->p;
		i = 0;
		while (i <= pc->shift_save)
		{
			location = pc->location % MEM_SIZE - i;
			if (location < 0)
				location += MEM_SIZE;
			c.x = c0.x + (location % 64) * f->char_width * 2;
			c.y = c0.y + (location / 64) * f->char_height;
			draw_rectangle(&(vm->gui), c, (t_coord){f->char_width * 2 - 1, f->char_height - 1}, (t_pix)0x00ff00u);
			i++;
		}
		elem = elem->next;
	}
}

int		draw_game_loop(t_vm *vm)
{
	t_font_cursor	fc;
	t_pix			black;
	t_coord			c0;

	war_cycle(vm);
	if (!vm->something_happened)
		return (0);
	vm->map[4095] = 0xff;
	black.i = 0;
	clear_image(vm->gui.image, vm->gui.screen_size, black);
	font_cursor_init(&fc, &(vm->fonts[2]), (t_coord){5, 5}, 0);
	font_cursor_print(&(vm->gui), &fc, "COREWAR ");
	fc.font = &(vm->fonts[1]);
	fc.c.y += vm->fonts[2].char_height - vm->fonts[1].char_height;
	font_cursor_print(&(vm->gui), &fc,
						"BY ALALAOUI DHADLEY LRAMIREZ STOUPIN\n");
	fc.c.y += 5;
	fc.font = &(vm->fonts[3]);
	c0 = fc.c;
	draw_map(vm, &fc);
	draw_processes(vm, c0, fc.font);
	mlx_put_image_to_window(vm->gui.mlx_ptr, vm->gui.mlx_win,
							vm->gui.image_ptr, 0, 0);
	return (0);
}

void	draw_game_clean(t_vm *vm)
{
	gui_clean(&(vm->gui));
	fonts_clean(vm);
	if (vm->gui.err)
		err2(vm, vm->gui.err_msg);
}
