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
#include "parsing/states.h"

static void		env_initialization(t_env *env)
{
	openfile_init(&(env->stdout), STDOUT_FILENO);
	openfile_init(&(env->stderr), STDERR_FILENO);
	env->header = 1;
	env->state = &state_start;
	env->line = 0;
	env->col = 0;
	env->err = 0;
	env->err_msg = NULL;
	cqueue_init(&(env->characters));
	env->pos = 0;
	env->op = NULL;
	pqueue_init(&(env->labels));
	pqueue_init(&(env->instructions));
	pqueue_init(&(env->instruction.arguments));
}

static void		env_clean(t_env *env)
{
	err_display(env);
	openfile_flush(&(env->stdout));
	openfile_flush(&(env->stderr));
	cqueue_delete(&(env->characters));
	pqueue_delete(&(env->labels));
	pqueue_delete(&(env->instructions));
	pqueue_delete(&(env->instruction.arguments));
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
		return (err(env, "non-printable character", 0));
	(env->state)(env, c);
	return (0);
}

static void		parse(t_env *env)
{
	char	c;
	int		ret;

	while (env->err == 0)
	{
		ret = openfile_read_char(&(env->input), &c);
		if (ret == -1)
			err(env, "unable to read input", 1);
		if (ret != 1)
			break ;
		parse_char(env, c);
	}
}

int				main(int ac, char **av)
{
	t_env		env;
	int			fd;

	env_initialization(&env);
	if (ac != 2 || av[1][0] == '\0')
	{
		openfile_write_str(&(env.stdout), "Usage: ", 0);
		openfile_write_str(&(env.stdout), av[0], 0);
		openfile_write_str(&(env.stdout), " file.s", 1);
		err(&env, "", 0);
	}
	fd = -1;
	if (env.err == 0 && (fd = open(av[1], O_RDONLY)) < 2)
		err(&env, "Unable to open input file", 1);
	if (env.err == 0)
		openfile_init(&(env.input), fd);
	if (env.err == 0)
		parse(&env);
	if (fd >= 2)
		close(fd);
//	create_champion(&env);
	env_clean(&env);
	return (0);
}
