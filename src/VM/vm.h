/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 14:44:18 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/26 18:17:52 by dhadley          ###   ########.fr       */
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
# define INT_MAX 2147483647
typedef struct		s_thread
{
	int			carry;
	int			r[REG_NUMBER + 1];
	int			cycles;
	int			location;
	int			countdown;
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
	t_champ			champs_fd[MAX_PLAYERS];
	t_pqueue		threads;
	char			map[MEM_SIZE];
	int				nb_champs;
	int				err;
	char			*err_msg;
	int				option[2];
	int				game_cycle;
	const t_op		*op;
}					t_vm;

/*
** error.c
*/

void				err2(t_vm *vm, char *err_msg);
void				err2_display(t_vm *vm);

/*
** thread.c
*/

t_thread			*create_thread(t_vm *vm);
void				thread_init(t_vm *vm);

/*
** champion.c
*/


void				parse_champion(t_vm *vm, int i);
void				read_champion(t_vm *vm, int i);
void				load_champion(t_vm *vm, char **av, int *i, int fd[MAX_ARGS_NUMBER]);
void				fill_map(t_vm *vm, int i);

/*
** draw_game.c
*/

void				draw_game_init(t_vm *vm);
void				draw_game(t_vm *vm);
void				draw_game_clean(t_vm *vm);

/*
** operations
*/

int					op_ld(t_vm *vm, t_thread PC);

/*
** dump.c
*/

void				parse_options(t_vm *vm, int *ac, char **av);
void				dump(t_vm *vm);

/*
** cycle.c
*/

void				war(t_vm *vm);
const t_op			*find_opcode(int pc);

#endif
