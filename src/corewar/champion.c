/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 15:16:28 by alalaoui          #+#    #+#             */
/*   Updated: 2018/03/06 19:28:10 by dhadley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "io/openfile.h"
#include "vm.h"

static int		check_magic(t_vm *vm, t_openfile *of)
{
	unsigned char	magic[4];
	int				ret;

	ret = openfile_read_buf(of, magic, 4, 0);
	if (ret < 0)
		return (err2(vm, "unable to read input file"));
	if (ret < 4)
		return (err2(vm, "input file too small"));
	if (magic[0] == 0x00 && magic[1] == 0xea
		&& magic[2] == 0x83 && magic[3] == 0xf3)
		return (0);
	return (err2(vm, "wrong magic number"));
}

static int		read_buffers(t_vm *vm, t_champ *champ, t_openfile *of)
{
	int			ret;

	ret = openfile_read_buf(of, champ->name, PROG_NAME_LENGTH, 0);
	if (ret < PROG_NAME_LENGTH)
		return (err2(vm, "unable to read program name"));
	champ->name[ret] = 0;
	if (openfile_read_buf(of, &(champ->size_bytecode), 8, 1) < 8)
		return (err2(vm, "unable to read program size"));
	if (champ->size_bytecode > CHAMP_MAX_SIZE)
		return (err2(vm, "champion too big"));
	if ((champ->bytecode = (char*)malloc(champ->size_bytecode)) == NULL)
		return (err2(vm, "champion too big for memory"));
	ret = openfile_read_buf(of, champ->comment, COMMENT_LENGTH, 0);
	if (ret < COMMENT_LENGTH)
		return (err2(vm, "unable to read program comment"));
	champ->comment[ret] = 0;
	if (openfile_skip(of, 4) < 4)
		return (err2(vm, "error while reading input file"));
	ret = openfile_read_buf(of, champ->bytecode, champ->size_bytecode, 0);
	if (ret < (long long int)champ->size_bytecode)
		return (err2(vm, "unable to read program bytecode"));
	champ->size = champ->size_bytecode + 4 + PROG_NAME_LENGTH + COMMENT_LENGTH;
	return (0);
}

int				champion_load(t_vm *vm, t_champ *champ, int n, char *file_name)
{
	int			fd;
	t_openfile	of;

	champ->number = n;
	champ->last_live = -1;
	if ((fd = open(file_name, O_RDONLY)) < 2)
		return (err2(vm, "unable to open input file"));
	openfile_init(&of, fd);
	if (check_magic(vm, &of))
	{
		close(fd);
		return (vm->err);
	}
	if (read_buffers(vm, champ, &of))
	{
		close(fd);
		return (vm->err);
	}
	if (champ->size_bytecode == 0 && !vm->zaz_mode)
		return (err2(vm, "chamption has no instructions"));
	return (0);
}

void			champion_to_vm(t_vm *vm, int i_champ)
{
	t_champ		*champ;
	size_t		i;
	size_t		pos;

	champ = &(vm->champs[i_champ]);
	pos = i_champ * (MEM_SIZE / vm->n_champs);
	i = 0;
	while (i < champ->size_bytecode)
	{
		vm->map[pos] = champ->bytecode[i];
		pos = (pos + 1) % MEM_SIZE;
		i++;
	}
}
