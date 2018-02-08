/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 15:16:28 by alalaoui          #+#    #+#             */
/*   Updated: 2018/02/08 11:51:49 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "vm.h"

void		fill_map(t_vm *vm, int i)
{
	ft_memcpy(&(vm->map[i * (MEM_SIZE / vm->nb_champs)]),
				&(vm->champs_fd[i].cor[16 + PROG_NAME_LENGTH + COMMENT_LENGTH]),
				vm->champs_fd[i].size);
}

void		parse_champion(t_vm *vm, int i)
{
	ft_memcpy(vm->champs_fd[i].name, vm->champs_fd[i].cor + 4,
				PROG_NAME_LENGTH);
	vm->champs_fd[i].sizeb = vm->champs_fd[i].cor[10 + PROG_NAME_LENGTH] << 8
								| vm->champs_fd[i].cor[11 + PROG_NAME_LENGTH];
	if (vm->champs_fd[i].sizeb != vm->champs_fd[i].size)
		err2(vm, "A champion has a code size that differ from its header");
}

void		read_champion(t_vm *vm, int i)
{
	int		ret;
	char	c;
	int		pos;

	pos = 0;
	while (vm->err == 0)
	{
		ret = openfile_read_char(&(vm->champs_fd[i].file), &c);
		if (ret == -1)
			err2(vm, "unable to read input");
		if (ret != 1)
			break ;
		vm->champs_fd[i].cor[pos++] = (unsigned char)c;
		if (pos >= MAX_SIZE)
			err2(vm, "file too large");
	}
	vm->champs_fd[i].size = (pos - PROG_NAME_LENGTH - COMMENT_LENGTH - 16);
}

static void	open_champ(t_vm *vm, char **av, int i, int *fd)
{
	if (vm->err == 0)
	{
		if ((*fd = open(av[i + 1], O_RDONLY)) < 2)
			err2(vm, "Unable to open input file");
	}
}

void		load_champion(t_vm *vm, char **av, int *i, int fd[MAX_ARGS_NUMBER])
{
	static int	id = -1;
	int			n;

	vm->n += check_option(vm, *i);
	n = check_option(vm, *i);
	open_champ(vm, av, ((*i) + vm->d + vm->v + vm->n), &fd[*i]);
	if (vm->err == 0)
	{
		openfile_init(&(vm->champs_fd[*i].file), fd[*i]);
		if (n == 0)
		{
			vm->champs_fd[*i].id = id;
			pqueue_push(&(vm->threads), create_thread(vm, id));
			id--;
		}
		else
		{
			vm->champs_fd[*i].id = vm->champ_n[*i];
			pqueue_push(&(vm->threads), create_thread(vm, vm->champ_n[*i]));
		}
		read_champion(vm, *i);
		parse_champion(vm, *i);
		fill_map(vm, *i);
		(*i)++;
	}
}
