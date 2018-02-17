/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 14:12:51 by stoupin           #+#    #+#             */
/*   Updated: 2018/02/16 18:45:13 by dhadley          ###   ########.fr       */
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
# define N_FONTS 4

typedef struct		s_champ
{
	int			number;
	size_t		size;
	size_t		size_bytecode;
	char		name[PROG_NAME_LENGTH + 1];
	char		comment[COMMENT_LENGTH + 1];
	char		*bytecode;
	int			last_live;

}					t_champ;

typedef struct		s_vm
{
	t_champ			champs[MAX_PLAYERS];
	int				n_champs;
	t_pqueue		threads;
	unsigned char	map[MEM_SIZE];
	int				err;
	int				cycle_to_dump;
	int				dump_every;
	int				verbose;
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
	int				winner;
}					t_vm;

typedef struct		s_thread
{
	int			number;
	int			carry;
	int			r[REG_NUMBER + 1];
	int			cycles;
	int			location;
	int			countdown;
	bool		alive;
	int			indent;
	char		bytecode;
	int			params[4];
	int			params_type[4];
	t_vm		*vm;
}					t_thread;

typedef enum		e_state
{
	S_START,
	S_D,
	S_N,
	S_S,
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
void				announce_war(t_vm *vm, int i);

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

void				op_live(t_thread *pc);
void				op_ld(t_thread *pc);
void				op_st(t_thread *pc);
void				op_add(t_thread *pc);
void				op_sub(t_thread *process);
void				op_and(t_thread *pc);
void				op_or(t_thread *pc);
void				op_xor(t_thread *pc);
void				op_zjmp(t_thread *process);
void				op_ldi(t_thread *process);
void				op_ldi_dir(t_thread *process);
void				op_ldi_reg(t_thread *process);
void				op_sti(t_thread *process);
void				op_sti_ind(t_thread *process);
void				op_sti_reg(t_thread *process);
void				op_fork(t_thread *process);
void				op_lld(t_thread *process);
void				op_lldi(t_thread *process);
void				op_lldi_dir(t_thread *process);
void				op_lldi_reg(t_thread *process);
void				op_lfork(t_thread *process);
void				op_aff(t_thread *process);

/*
** params.c
*/

int					check_params(unsigned char byte, int number);
int					recup_param(t_vm *vm, int location, int size);

/*
** getters.c
*/

int					get(t_thread *pc, int param_nbr);
int					get_byte_at(t_thread *pc, int amount, bool indent);

/*
** setters.c
*/

void				set(t_thread *pc, int param_nbr, int value);
void				set_bytes(t_thread *pc, int param, int value);

/*
** params_new.c
*/

int					shift_loc(t_thread *pc, int amount);

/*
** dump.c
*/

void				write_map(t_vm *vm);
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

void				print_op(t_vm *vm, t_thread *pc);
int					op_exit(t_thread *pc, int cycles, bool carry);
int					op_success(t_thread *pc, int cycles, int loc, bool carry);

/*
** verbose.c
*/

void				print_instruction_start(t_vm *vm, t_thread *pc);
void				print_instruction_continue(t_vm *vm, t_thread *pc);
void				print_str(t_vm *vm, char *s, int endl);
void				print_nbr(t_vm *vm, int i, int endl);
void				print_reg(t_vm *vm, int i, int endl);

#endif
