/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 15:49:30 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/17 13:48:37 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "asm.h"
#include "parsing/states.h"
#include <stdlib.h>

static void		env_initialization(t_env *env)
{
	openfile_init(&(env->stdout), STDOUT_FILENO);
	openfile_init(&(env->stderr), STDERR_FILENO);
	crc32_init(&(env->hash_env));
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
}

static void		env_clean(t_env *env)
{
	t_pqueue_elem	*elem;

	err_display(env);
	openfile_flush(&(env->stdout));
	openfile_flush(&(env->stderr));
	cqueue_delete(&(env->characters));
	pqueue_delete(&(env->labels));
	elem = env->instructions.first;
	while (elem)
	{
		if (((t_instruction*)(elem->p))->is_lab)
			;
		else
			instruction_clean((t_instruction*)elem->p);
		elem = elem->next;
	}
	instruction_clean(&(env->instruction));
	pqueue_delete(&(env->instructions));
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
	if (env->err)
		return ;
	if (!find_labels(env))
		err(env, "label not found", -1);
}

//A SUPPRIMER AVANT PUSH
/*
static void		print_champ(t_pqueue *instructions)
{
	t_pqueue_elem	*tmp;
	t_instruction	*inst;
	t_label			*lab;
	int				i;
	int				j;

	i = 0;
	tmp = instructions->first;
	while (i++ < instructions->len)
	{
		inst = tmp->p;
		lab = tmp->p;
		if (inst->is_lab)
		{	
			printf("LABEL:%s\n", lab->name);

		}
		else
		{
			printf("INSTRUCTION:%s\n", inst->op->name);
			j = 0;
			while (j < inst->len)
			{
				printf("ARG-%d:%s\n", j, inst->arguments[j]->name);
				j++;
			}
		}
		tmp = tmp->next;
	}
}*/

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
		err(&env, "", -1);
	}
	fd = -1;
	if (env.err == 0 && (fd = open(av[1], O_RDONLY)) < 2)
		err(&env, "Unable to open input file", 1);
	//check if .s and save as .cor in env->file_name;
	char *tmp;
	tmp = (char *)malloc(sizeof(char) * ft_strlen(av[1]) + 3);
	ft_strcpy(tmp, av[1]);
	tmp[ft_strlen(av[1]) - 1] = 't';
	tmp[ft_strlen(av[1])] = '\0';
	env.file_name = tmp;


	if (env.err == 0)
		openfile_init(&(env.input), fd);
	if (env.err == 0)
		parse(&env);
	if (fd >= 2)
		close(fd);
	assemble(&env);
	init_cor(&env);
//	print_champ(&env.instructions);
	//	create_champion(&env);
	env_clean(&env);
	return (0);
}
