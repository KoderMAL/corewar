/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 10:53:17 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/19 17:43:19 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>
#include <unistd.h>

void	write_magic(int fd)
{
	char magic[3];

	magic[0] = 0xea;
	magic[1] = 0x83;
	magic[2] = 0xf3;
	write(fd, magic, 3);
}

void	write_comment(int fd, t_env *env)
{
	char	size[2];

	if (env->prog_size > 255)
		size[0] = (env->prog_size >> 8);
	else
		size[0] = '\0';	
	size[1] = (env->prog_size & 255);
	write(fd, size, 2);
	write(fd, env->comment, COMMENT_LENGTH);
}

void	write_prog_name(int fd, t_env *env)
{
	write(fd, env->name, PROG_NAME_LENGTH);
}

void	init_cor(t_env *env)
{
	int		fd;

	fd = open(env->file_name, O_CREAT | O_WRONLY, S_IRWXU); //check mode and fd
	if (fd > 1)
	{
		write(fd, "\0", 1);
		write_magic(fd);
		write_prog_name(fd, env);
		write(fd, "\0\0\0\0\0\0", 6);
		write_comment(fd, env);
		write(fd, "\0\0\0\0", 4);
		write(fd, env->champion, env->prog_size);
	}
}
