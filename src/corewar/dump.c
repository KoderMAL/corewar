/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 12:00:20 by alalaoui          #+#    #+#             */
/*   Updated: 2018/03/06 17:55:39 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/ft.h"
#include "vm.h"

static void	write_hex(t_vm *vm, unsigned char byte)
{
	static const char	digits[16] = "0123456789abcdef";

	openfile_write_char(&(vm->stdout), digits[byte / 16]);
	openfile_write_char(&(vm->stdout), digits[byte % 16]);
}

void		write_map(t_vm *vm)
{
	unsigned char	byte;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < MEM_SIZE / 64)
	{
		openfile_write_str(&(vm->stdout), "0x", 0);
		write_hex(vm, (i * 64) / 256);
		write_hex(vm, (i * 64) % 256);
		openfile_write_str(&(vm->stdout), " : ", 0);
		j = 0;
		while (j < 64)
		{
			byte = vm->map[64 * i + j];
			write_hex(vm, byte);
			openfile_write_char(&(vm->stdout), ' ');
			j++;
		}
		openfile_write_char(&(vm->stdout), '\n');
		i++;
	}
}

void		dump(t_vm *vm)
{
	if ((vm->cycle_to_dump != -1 && vm->game_cycle == vm->cycle_to_dump)
		|| (vm->dump_every > 0 && vm->game_cycle % vm->dump_every == 0))
	{
		write_map(vm);
		if (vm->game_cycle == vm->cycle_to_dump)
			vm_clean(vm);
	}
}
