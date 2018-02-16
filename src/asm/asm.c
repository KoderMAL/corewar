/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 15:49:30 by alalaoui          #+#    #+#             */
/*   Updated: 2018/02/16 14:24:49 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "asm.h"
#include "parsing/states.h"

static void		env_initialization(t_env *env)
{
	openfile_init(&(env->stdout), STDOUT_FILENO);
	openfile_init(&(env->stderr), STDERR_FILENO);
	env->header = 1;
	env->state = &state_start;
	env->line = 0;
	env->name_check = 0;
	env->comment_check = 0;
	env->col = 0;
	env->err = 0;
	env->err_msg = NULL;
	cqueue_init(&(env->characters));
	env->pos = 0;
	env->op = NULL;
	pqueue_init(&(env->labels));
	instruction_init(&(env->instruction), NULL);
	pqueue_init(&(env->instructions));
	ft_memset(env->name, '\0', PROG_NAME_LENGTH);
	ft_memset(env->comment, '\0', COMMENT_LENGTH);
	env->champion = NULL;
	env->file_name = NULL;
}

static void		env_clean(t_env *env)
{
	t_pqueue_elem	*elem;

	err_display(env);
	openfile_flush(&(env->stdout));
	openfile_flush(&(env->stderr));
	cqueue_delete(&(env->characters));
	pqueue_clean(&(env->labels));
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
	if (env->champion)
		free(env->champion);
	if (env->file_name)
		free(env->file_name);
}

static void		print_usage(t_env *env, char **argv)
{
	openfile_write_str(&(env->stdout), "Usage: ", 0);
	openfile_write_str(&(env->stdout), argv[0], 0);
	openfile_write_str(&(env->stdout), " file.s", 1);
	err(env, "", -1);
}

static int		set_cor_file_name(t_env *env, char *s_file_name)
{
	char	*cor_file_name;
	size_t	len;

	len = ft_strlen(s_file_name);
	cor_file_name = (char *)malloc(sizeof(char) * len + 3);
	if (cor_file_name == NULL)
		return (err(env, "memory error", -1));
	ft_strcpy(cor_file_name, s_file_name);
	ft_strcpy(cor_file_name + len - 1, "cor");
	env->file_name = cor_file_name;
	return (0);
}

int				main(int argc, char **argv)
{
	t_env		env;
	int			fd;

	env_initialization(&env);
	if (argc != 2 || argv[1][0] == '\0')
		print_usage(&env, argv);
	fd = -1;
	if (env.err == 0 && (fd = open(argv[1], O_RDONLY)) < 2)
		err(&env, "Unable to open input file", 1);
	if (env.err == 0)
		set_cor_file_name(&env, argv[1]);
	if (env.err == 0)
		openfile_init(&(env.input), fd);
	if (env.err == 0)
		parse_input(&env);
	if (fd >= 2)
		close(fd);
	if (env.err == 0)
		assemble(&env);
	if (env.err == 0)
		write_cor(&env);
	env_clean(&env);
	return (env.err);
}
