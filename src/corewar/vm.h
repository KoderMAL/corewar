/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 14:44:18 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/29 10:34:22 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "asm/op.h"
# include "io/openfile.h"
# include "util/pqueue.h"
# include "gui/gui.h"
# include "gui/font.h"
# include "ft/ft.h"

# define ABS(X)	((X > 0) ? X : -(X))
# define MAX_SIZE (PROG_NAME_LENGTH + COMMENT_LENGTH + CHAMP_MAX_SIZE + 14)

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

# define N_FONTS 4

typedef struct		s_vm
{
	t_champ			champs_fd[MAX_PLAYERS];
	t_pqueue		threads;
	unsigned char	map[MEM_SIZE];
	int				nb_champs;
	int				err;
	int				champ_n[4];
	int				cycle_to_dump;
	char			*err_msg;
	int				game_cycle;
	int				v;
	int				d;
	const t_op		*op;
	int				draw_game;
	t_gui			gui;
	t_font			fonts[N_FONTS];
}					t_vm;

typedef enum e_state
{
	S_START,
	S_D,
	S_N,
	S_CHAMP
}			t_state;

/*
** vm.c
*/

void				vm_init(t_vm *vm);
void				vm_clean(t_vm *vm);

/*
** parse_args.c
*/

int 				parse_args(t_vm *vm, int ac, char **av);
int					check_option(t_vm *vm, int i);

/*
** error.c
*/

int					err2(t_vm *vm, char *err_msg);
void				err2_display(t_vm *vm);

/*
** thread.c
*/

t_thread			*create_thread(t_vm *vm, int n);
t_thread			*dup_thread(t_thread *src_thread, int pc);

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

int					draw_game_init(t_vm *vm);
void				draw_game_loop(t_vm *vm);
void				draw_game_clean(t_vm *vm);

/*
** operations
*/

void				op_live(t_vm *vm, t_thread *PC);
void				op_zjmp(t_vm *vm, t_thread *process);
void				op_fork(t_vm *vm, t_thread *process);
int					op_ld(t_vm *vm, t_thread *PC);
void				op_aff(t_vm *vm, t_thread *process);
void				op_add(t_vm *vm, t_thread *process);
void				op_sub(t_vm *vm, t_thread *process);
int					op_and(t_vm *vm, t_thread *pc);
// int					op_or(t_vm *vm, t_thread *pc);
// int					op_xor(t_vm *vm, t_thread *pc);

/*
** params.c
*/

int					check_params(unsigned char byte, int number);
int					recup_param(t_vm *vm, int location, int size);

/*
** dump.c
*/

void				parse_options(t_vm *vm, int *ac, char **av);
int					parse_number(t_vm *vm, char **av, int *i);
void				dump(t_vm *vm);

/*
** cycle.c
*/

void				war_cycle(t_vm *vm);
const t_op			*find_opcode(int pc);

#endif