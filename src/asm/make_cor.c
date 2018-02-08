/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 10:53:17 by dhadley           #+#    #+#             */
/*   Updated: 2018/02/08 11:32:04 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/stat.h>
#include "io/openfile.h"
#include "asm.h"

void	write_magic(t_openfile *of)
{
	char magic[3];

	magic[0] = 0xea;
	magic[1] = 0x83;
	magic[2] = 0xf3;
	openfile_write_buf(of, magic, 3);
}

void	write_comment(t_openfile *of, t_env *env)
{
	char	size[2];

	if (env->prog_size > 255)
		size[0] = (env->prog_size >> 8);
	else
		size[0] = '\0';
	size[1] = (env->prog_size & 255);
	openfile_write_buf(of, size, 2);
	openfile_write_buf(of, env->comment, COMMENT_LENGTH);
}

void	write_prog_name(t_openfile *of, t_env *env)
{
	openfile_write_buf(of, env->name, PROG_NAME_LENGTH);
}

void	write_cor(t_env *env)
{
	int			fd;
	t_openfile	of;

	fd = open(env->file_name, O_CREAT | O_WRONLY, S_IRWXU);
	if (fd > 1)
	{
		openfile_init(&of, fd);
		openfile_write_char(&of, '\0');
		write_magic(&of);
		write_prog_name(&of, env);
		openfile_write_buf(&of, "\0\0\0\0\0\0", 6);
		write_comment(&of, env);
		openfile_write_buf(&of, "\0\0\0\0", 4);
		openfile_write_buf(&of, (char*)env->champion, env->prog_size);
		openfile_flush(&of);
	}
	else
		err(env, "unable to write output file", -1);
}
