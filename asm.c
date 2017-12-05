/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 15:49:30 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/05 14:27:32 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdio.h>

int			main(int ac, char **av)
{
	t_openfile	of;
	t_openfile	of2;
	char		c;
	int			fd;

	if (ac != 2 || ft_strlen(av[1]) < 2 || (av[1][ft_strlen(av[1]) - 1] != 's'
				&& av[1][ft_strlen(av[1]) - 2] != '.'))
	{
		write(1, "usage: ./asm [file.s]\n", 22);
		return (-1);
	}
	if (!(fd = open(av[1], O_RDONLY)))
		return (-1);
	openfile_init(&of, fd);
	openfile_init(&of2, STDOUT_FILENO);
	while ((openfile_read_char(&of, &c) == 1))
		openfile_write_char(&of2, c);
	openfile_flush(&of2);
//	printf("buffer:\n%s", of2.buffer);
	return (0);
}
