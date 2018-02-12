/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 14:12:51 by stoupin           #+#    #+#             */
/*   Updated: 2018/02/12 17:38:16 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <unistd.h>
# include <stdbool.h>
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
	bool		alive;
}					t_thread;

typedef struct		s_champ
{
	int			number;
	size_t		size;
	size_t		size_bytecode;
	char		name[PROG_NAME_LENGTH + 1];
	char		comment[COMMENT_LENGTH + 1];
	char		*bytecode;

}					t_champ;

# define N_FONTS 4

typedef struct		s_vm
{
	t_champ			champs[MAX_PLAYERS];
	int				n_champs;
	t_pqueue		threads;
	unsigned char	map[MEM_SIZE];
	int				err;
	int				cycle_to_dump;
	char			*err_msg;
	int				game_cycle;
	int				num_lives;
	int				cycle_to_die;
	int				num_checkups;
	const t_op		*op;
	int				draw_game;
	t_gui			gui;
	t_font			fonts[N_FONTS];
	t_openfile		stdout;
	t_openfile		stderr;
}					t_vm;

typedef enum		e_state
{
	S_START,
	S_D,
	S_N,
	S_CHAMP
}					t_state;

/*
** vm.c
*/

void				vm_init(t_vm *vm);
void				vm_clean(t_vm *vm);

/*
** parse_args.c
*/

int					parse_args(t_vm *vm, int ac, char **av);
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

int					champion_load(t_vm *vm, t_champ *champ, int n,
									char *file_name);
void				champion_to_vm(t_vm *vm, int i_champ);

/*
** draw_game.c
*/

int					draw_game_init(t_vm *vm);
int					draw_game_loop(t_vm *vm);
void				draw_game_clean(t_vm *vm);

/*
** operations
*/

int					op_live(t_vm *vm, t_thread *pc);
int					op_ld(t_vm *vm, t_thread *pc);
int					op_st(t_vm *vm, t_thread *pc);
int					op_add(t_vm *vm, t_thread *process);
int					op_sub(t_vm *vm, t_thread *process);
int					op_and(t_vm *vm, t_thread *pc);
int					op_or(t_vm *vm, t_thread *pc);
int					op_xor(t_vm *vm, t_thread *pc);
int					op_zjmp(t_vm *vm, t_thread *process);
int					op_ldi(t_vm *vm, t_thread *process);
int					op_ldi_dir(t_vm *vm, t_thread *process);
int					op_ldi_reg(t_vm *vm, t_thread *process);
int					op_sti(t_vm *vm, t_thread *process);
int					op_sti_reg(t_vm *vm, t_thread *process);
int					op_fork(t_vm *vm, t_thread *process);
int					op_lld(t_vm *vm, t_thread *process);
int					op_lldi(t_vm *vm, t_thread *process);
int					op_lldi_dir(t_vm *vm, t_thread *process);
int					op_lldi_reg(t_vm *vm, t_thread *process);
int					op_lfork(t_vm *vm, t_thread *process);
int					op_aff(t_vm *vm, t_thread *process);

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

/*
** check_cycles.c
*/

void				check_cycles(t_vm *vm);

/*
** other
*/

int					op_exit(t_thread *pc, int cycles, bool carry);
int					op_success(t_thread *pc, int cycles, int loc, bool carry);

#endif
