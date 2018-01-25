/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 14:44:18 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/25 16:33:07 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "main/op.h"
#include "io/openfile.h"
#include "ft/ft.h"
#include "util/pqueue.h"
# define MAX_SIZE (PROG_NAME_LENGTH + COMMENT_LENGTH + CHAMP_MAX_SIZE + 14)

typedef struct		s_thread
{
	int			carry;
	int			r[REG_NUMBER];
	int			cycles;
	int			location;
}					t_thread;

typedef struct		s_champ
{
	t_openfile	file;
	int			id;
	short		sizeb;
	short		size;
	char		name[PROG_NAME_LENGTH];
	char		comment[COMMENT_LENGTH];
	char		cor[MAX_SIZE];
}					t_champ;

typedef struct		s_vm
{
	t_champ			champs_fd[4];
	t_pqueue		threads;
	char			map[MEM_SIZE];
	int				nb_champs;
	int				err;
	char			*err_msg;
}					t_vm;

void 				fill_map();

/*
** error.c
*/

void				err2(t_vm *vm, char *err_msg);
void				err2_display(t_vm *vm);

/*
** thread.c
*/

t_thread			*create_thread();
void				thread_init(t_vm *vm);

/*
** champion.c
*/


void				parse_champion(t_vm *vm, int i);
void				read_champion(t_vm *vm, int i);
void				load_champion(t_vm *vm, char **av, int *i, int fd[MAX_ARGS_NUMBER]);

#endif
