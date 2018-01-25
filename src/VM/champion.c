/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 15:16:28 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/25 15:02:37 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		parse_champion(t_vm *vm, int i)
{
	ft_memcpy(vm->champs_fd[i].name, vm->champs_fd[i].cor, PROG_NAME_LENGTH);
}

void		read_champion(t_vm *vm, int i)
{
	int ret;
	char c;
	int pos;

	pos = 0;
	while (vm->err == 0)
	{
		ret = openfile_read_char(&(vm->champs_fd[i].file), &c);
		if (ret == -1)
			err2(vm, "unable to read input");
		if (ret != 1)
			break;
		vm->champs_fd[i].cor[pos++] = c;
		if (pos >= MAX_SIZE)
			err2(vm, "file too large");
	}
}

void		load_champion(t_vm *vm, char **av, int *i, int fd[MAX_ARGS_NUMBER])
{
	if (vm->err == 0 && (fd[*i] = open(av[(*i) + 1], O_RDONLY)) < 2)
		err2(vm, "Unable to open input file");
	printf("\nFD:%d\n", fd[*i]);
	if (vm->err == 0)
	{
		openfile_init(&(vm->champs_fd[*i].file), fd[*i]);
		ft_memset(vm->champs_fd[*i].file.buffer, 0, BUFF_SIZE);
		ft_memset(vm->champs_fd[*i].cor, 0, MAX_SIZE);
		ft_memset(vm->champs_fd[*i].name, 0, PROG_NAME_LENGTH);
		ft_memset(vm->champs_fd[*i].comment, 0, COMMENT_LENGTH);
	}
	read_champion(vm, *i);
	parse_champion(vm, *i);
	(*i)++;
}