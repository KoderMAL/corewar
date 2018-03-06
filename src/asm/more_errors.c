/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 15:57:32 by dhadley           #+#    #+#             */
/*   Updated: 2018/03/06 18:12:18 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "asm.h"

static void	no_code(void)
{
	write(1, "Warning: Champion has no code\n", 30);
}

static void	no_comment(void)
{
	write(1, "Warning: Champion has no comment\n", 33);
}

static void	no_name(t_env *env)
{
	int		fd;
	char	buf[23115];
	int		ret;
	int		len;

	len = 23115;
	ret = 0;
	if ((fd = open("src/asm/no_name.txt", O_RDONLY)) < 2)
		err(env,
				"Unable to open no_name.txt\nWarning: Champion has no name", 1);
	if (env->err == 0)
		ret = read(fd, buf, len);
	if (ret == len)
		write(1, buf, len);
	else
		err(env,
				"Unable to read no_name.txt\nWarning: Champion has no name", 1);
}

void		check_warnings(t_env *env)
{
	if (env->name[0] == 0)
		no_name(env);
	if (env->prog_size == 0)
		no_code();
	if (env->comment[0] == 0)
		no_comment();
}
