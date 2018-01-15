/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhadley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 10:53:17 by dhadley           #+#    #+#             */
/*   Updated: 2018/01/15 18:23:53 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>
#include <unistd.h>

void	init_cor(t_env *env)
{
	int		fd;

	fd = open(env->file_name, O_CREAT | O_WRONLY); //check mode and fd
	if (fd > 1)
	{
		write(fd, env->champion, CHAMP_MAX_SIZE - 1);
		printf("bipbop\n");
	}
}
