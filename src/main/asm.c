/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 15:49:30 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/05 18:17:11 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "asm.h"
#include "parsing/parsing.h"
#include "ft/ft.h"

static void		env_initialization(t_env *env, int fd)
{
	openfile_init(&env->input, fd);
	openfile_init(&env->output, STDOUT_FILENO);
	env->state = &state_0;
	env->name_length = 0;
	env->comment_length = 0;
	env->line = 0;
	env->col = 0;
	env->err = 0;
	env->err_msg = NULL;
	ft_bzero(env->name, PROG_NAME_LENGTH);
	ft_bzero(env->comment, COMMENT_LENGTH);
}

int				main(int ac, char **av)
{
	t_env		env;
	char		c;
	int			fd;

	if (ac != 2 || ft_strlen(av[1]) < 2 || (av[1][ft_strlen(av[1]) - 1] != 's'
				&& av[1][ft_strlen(av[1]) - 2] != '.'))
	{
		write(1, "usage: ./asm [file.s]\n", 22);
		return (-1);
	}
	if ((fd = open(av[1], O_RDONLY)) < 2)
		return (-1);
	env_initialization(&env, fd);
	while ((openfile_read_char(&(env.input), &c) == 1))
	{
		openfile_write_char(&(env.output), c);
		//printf("letter:%c\n", c);
		(env.state)(&env, c);
		ft_error_check(env.err, env.err_msg);
	}
	openfile_flush(&(env.output));
	close(fd);
	return (0);
}
