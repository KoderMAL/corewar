/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 15:49:30 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/08 18:46:10 by alalaoui         ###   ########.fr       */
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
	env->reread = 0;
	env->labels = NULL;
}

static void		parse(t_env *env)
{
	char c;

	while (env->err == 0)
	{
		if (env->reread == 0)
		{
			if (openfile_read_char(&(env->input), &c) != 1)
				break ;
			openfile_write_char(&(env->output), c);
		}
		else
			env->reread = 0;
		(env->state)(env, c);
		ft_line_col(env, c);
		ft_error_check(env->err, env->err_msg);
	}
}

int				main(int ac, char **av)
{
	t_env		env;
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
	parse(&env);
	openfile_flush(&(env.output));
	close(fd);
//	create_champion(&env);
	return (0);
}
