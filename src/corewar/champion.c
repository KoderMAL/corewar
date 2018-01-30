/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 15:16:28 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/30 18:18:10 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "ft/ft.h"
#include "vm.h"

void fill_map(t_vm *vm, int i)
{
	printf("SIZE:%d\n", vm->champs_fd[i].sizeb);
	ft_memcpy(&(vm->map[i * (MEM_SIZE / vm->nb_champs)]),
			  &(vm->champs_fd[i].cor[16 + PROG_NAME_LENGTH + COMMENT_LENGTH]),
			  vm->champs_fd[i].size);
}

void parse_champion(t_vm *vm, int i)
{
	ft_memcpy(vm->champs_fd[i].name, (vm->champs_fd[i].cor + 4), PROG_NAME_LENGTH);
	vm->champs_fd[i].sizeb = vm->champs_fd[i].cor[10 + PROG_NAME_LENGTH] << 8 | vm->champs_fd[i].cor[11 + PROG_NAME_LENGTH];
	if (vm->champs_fd[i].sizeb != vm->champs_fd[i].size)
		err2(vm, "A champion has a code size that differ from its header");
}

void read_champion(t_vm *vm, int i)
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

static void open_champ(t_vm *vm, char **av, int i, int fd[MAX_ARGS_NUMBER])
{
/*	if (vm->draw_game == 1)
	{
		printf("ARG:%s\n", av[i + 2]);
		if (vm->err == 0 && (fd[i] = open(av[i + 2], O_RDONLY)) < 2)
			err2(vm, "Unable to open input file");
	}
	else if (vm->cycle_to_dump != -1)
	{
		printf("ARG:%s\n", av[i + 2 + 1]);
		if (vm->err == 0 && (fd[i] = open(av[i + 2 + 1], O_RDONLY)) < 2)
			err2(vm, "Unable to open input file");
	}
	else
	{*/
		printf("ARG:%s\n", av[i]);
		if (vm->err == 0 && (fd[i] = open(av[(*i + vm->d + vm->v + n)], O_RDONLY)) < 2)
			err2(vm, "Unable to open input file");
	//}
}

void load_champion(t_vm *vm, char **av, int *i, int fd[MAX_ARGS_NUMBER])
{
	static int id = -1;
	int n;

	n = check_option(av, *i);
	printf("WHERE AM I:%s || i =%d\n", av[(*i + vm->d + vm->v + n)], *i);
	open_champ(vm, av, (*i + vm->d + vm->v + n), fd);
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
	printf("champion id:%d\nchampname:%s\n", vm->champs_fd[*i].id, vm->champs_fd[*i].name);
}