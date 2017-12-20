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
	openfile_init(&(env->input), fd);
	openfile_init(&(env->stdout), STDOUT_FILENO);
	openfile_init(&(env->stderr), STDERR_FILENO);
	env->state = &state_0;
	env->name_length = 0;
	env->comment_length = 0;
	env->line = 0;
	env->col = 0;
	env->err = 0;
	env->err_msg = NULL;
	env->reread = 0;
	env->labels = NULL;
}

static void		env_clean(t_env *env)
{
	openfile_flush(&(env->stdout));
	openfile_flush(&(env->stderr));
}

static int		parse_char(t_env *env, char c)
{
	env->col++;
	if (c == '\t')
	{
		env->col += 3;
		openfile_write_str(&(env->stdout), "    ", 0);
	}
	else if (c == '\n')
	{
		env->col = 0;
		env->line++;
		openfile_write_char(&(env->stdout), '\n');
	}
	else if (ft_isprint(c))
		openfile_write_char((&env->stdout), c);
	else
		return (ft_err(env, "wrong character"));
	(env->state)(env, c);
	return (0);
}

static void		parse(t_env *env)
{
	char	c;
	int		ret;

	while (env->err == 0)
	{
		if (env->reread == 0)
		{
			ret = openfile_read_char(&(env->input), &c);
			if (ret == -1)
				ft_err(env, "unable to read input");
			if (ret != 1)
				break ;
		}
		env->reread = 0;
		parse_char(env, c);
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
	close(fd);
	env_clean(&env);
//	create_champion(&env);
	return (0);
}
