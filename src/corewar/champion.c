/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 15:16:28 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/29 17:03:39 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "ft/ft.h"
#include "vm.h"

void		fill_map(t_vm *vm, int i)
{
	printf("SIZE:%d\n", vm->champs_fd[i].sizeb);
	ft_memcpy(&(vm->map[i * (MEM_SIZE / vm->nb_champs)]),
		&(vm->champs_fd[i].cor[16 + PROG_NAME_LENGTH + COMMENT_LENGTH]),
		vm->champs_fd[i].size);
}

void		parse_champion(t_vm *vm, int i)
{
	ft_memcpy(vm->champs_fd[i].name, (vm->champs_fd[i].cor + 4), PROG_NAME_LENGTH);
	vm->champs_fd[i].sizeb = vm->champs_fd[i].cor[10 + PROG_NAME_LENGTH] << 8 | vm->champs_fd[i].cor[11 + PROG_NAME_LENGTH];
	if (vm->champs_fd[i].sizeb != vm->champs_fd[i].size)
		err2(vm, "A champion has a code size that differ from its header");
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
		vm->champs_fd[i].cor[pos++] = (unsigned char)c;
		if (pos >= MAX_SIZE)
			err2(vm, "file too large");
	}
	vm->champs_fd[i].size = (pos - PROG_NAME_LENGTH - COMMENT_LENGTH - 16);
}

void		load_champion(t_vm *vm, char **av, int *i, int fd[MAX_ARGS_NUMBER])
{
	static int id = -1;
	int		n;
	
	n = 0;
	if ((n = parse_number(vm, av, i)) == 0)
		err2(vm, "Player cant take a null number")
	if (vm->draw_game == 1) 
	{
		if (vm->err == 0 && (fd[*i] = open(av[*i + 2], O_RDONLY)) < 2)
			err2(vm, "Unable to open input file");
	}
	else
	{
		if (vm->err == 0 && (fd[*i] = open(av[(*i + (vm->option[0] * 2)) + 1], O_RDONLY)) < 2)
			err2(vm, "Unable to open input file");
	}
	printf("\nFD:%d\n", fd[*i]);
	if (vm->err == 0)
	{
		openfile_init(&(vm->champs_fd[*i].file), fd[*i]);
		ft_memset(vm->champs_fd[*i].file.buffer, 0, BUFF_SIZE);
		ft_memset(vm->champs_fd[*i].cor, 0, MAX_SIZE);
		ft_memset(vm->champs_fd[*i].name, 0, PROG_NAME_LENGTH);
		ft_memset(vm->champs_fd[*i].comment, 0, COMMENT_LENGTH);
		if (n == 0)
		{
			vm->champs_fd[*i].id = id;
			id--;
		}
		else 
  		    vm->champs_fd[*i].id = n; 
		read_champion(vm, *i);
		parse_champion(vm, *i);
		fill_map(vm, *i);
		(*i)++;
	}
	printf("champion id:%d\nchampname:%s\n", vm->champs_fd[*i].id, vm->champs_fd[*i].name);
}