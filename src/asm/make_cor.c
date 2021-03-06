/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 10:53:17 by dhadley           #+#    #+#             */
/*   Updated: 2018/03/06 16:28:58 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include "io/openfile.h"
#include "asm.h"

void	write_magic(t_openfile *of)
{
	char magic[3];

	magic[0] = 0xea;
	magic[1] = 0x83;
	magic[2] = 0xf3;
	openfile_write_buf(of, magic, 3, 0);
}

void	write_size(t_openfile *of, t_env *env)
{
	openfile_write_buf(of, (char*)&(env->prog_size), sizeof(env->prog_size), 1);
}

void	write_comment(t_openfile *of, t_env *env)
{
	openfile_write_buf(of, env->comment, COMMENT_LENGTH, 0);
}

void	write_prog_name(t_openfile *of, t_env *env)
{
	openfile_write_buf(of, env->name, PROG_NAME_LENGTH, 0);
}

void	write_cor(t_env *env)
{
	int			fd;
	t_openfile	of;

	fd = open(env->file_name, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR + S_IWUSR);
	if (fd > 1)
	{
		openfile_init(&of, fd);
		openfile_write_char(&of, '\0');
		write_magic(&of);
		write_prog_name(&of, env);
		write_size(&of, env);
		write_comment(&of, env);
		openfile_write_buf(&of, "\0\0\0\0", 4, 0);
		openfile_write_buf(&of, (char*)env->champion, env->prog_size, 0);
		openfile_flush(&of);
		write(1, "Writing output program to ", 26);
		write(1, env->file_name, ft_strlen(env->file_name));
		write(1, "\n", 1);
		check_warnings(env);
	}
	else
		err(env, "unable to write output file", -1);
}
