/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 14:44:18 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/22 16:59:57 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

#include "main/op.h"
#include "io/openfile.h"
#include "ft/ft.h"
#include "util/pqueue.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct		s_thread
{
	int			carry;
	int			reg1;
	int			reg2;
	int			reg3;
	int			location;
}					t_thread;

typedef struct		s_champ
{
	t_openfile	file;
	char		name[CHAMP_MAX_SIZE];
}					t_champ;

typedef struct		s_vm
{
	t_champ			champs_fd[4];
	char			map[MEM_SIZE];
	t_pqueue		*threads;
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

#endif