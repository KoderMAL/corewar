/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 11:40:49 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/30 16:47:30 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar/vm.h"

int		fonts_load(t_vm *vm)
{
	static const char	*fonts[N_FONTS] = {"fonts/font_small.bin",
						"fonts/font_medium.bin",
						"fonts/font_large.bin",
						"fonts/matrix.bin"};
	int					i;

	i = 0;
	while (i < N_FONTS)
	{
		font_load(&(vm->fonts[i]), fonts[i]);
		if (vm->fonts[i].err)
			return (err2(vm, vm->fonts[i].err_msg));
		i++;
	}
	return (0);
}

void	fonts_clean(t_vm *vm)
{
	int	i;

	i = 0;
	while (i < N_FONTS)
	{
		font_clean(&(vm->fonts[i]));
		i++;
	}
}
