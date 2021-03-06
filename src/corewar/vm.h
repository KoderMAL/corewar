/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 14:12:51 by stoupin           #+#    #+#             */
/*   Updated: 2018/03/05 18:35:15 by alalaoui         ###   ########.fr       */
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
# define PARAM1 1
# define PARAM2 2
# define PARAM3 4

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
	int				zaz_mode;
	char			*err_msg;
	int				game_cycle;
	int				num_lives;
	int				base_cycle_to_die;
	int				cycle_to_die;
	int				num_checkups;
	int				draw_game;
	t_gui			gui;
	t_font			fonts[N_FONTS];
	t_openfile		stdout;
	t_openfile		stderr;
	bool			something_happened;
	int				thread_counter;
	int				played_last;
	int				n;
	int				n_is_set;
	void			(*state)(struct s_vm *vm, char *av);
}					t_vm;

typedef struct		s_thread
{
	int				number;
	int				carry;
	int				r[REG_NUMBER + 1];
	const t_op		*op;
	int				cycles;
	int				location;
	int				countdown;
	bool			alive;
	int				last_live;
	int				shift;
	int				shift_save;
	int				adv;
	unsigned char	bytecode;
	int				params[4];
	int				params_type[4];
	bool			is_valid;
	t_vm			*vm;
}					t_thread;

typedef enum		e_state
{
	S_START,
	S_D,
	S_N,
	S_S,
	S_CHAMP
}					t_state;

typedef	struct		s_op_assoc
{
	int			opcode;
	void		(*op_function)(t_thread *process);
	int			print_value;
}					t_op_assoc;

const t_op			*get_op_by_code(int pc);

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
void				state_start(t_vm *vm, char *av);
void				state_champ(t_vm *vm, char *av);
void				state_s(t_vm *vm, char *av);
void				state_d(t_vm *vm, char *av);
void				state_n(t_vm *vm, char *av);
int					is_number_available(t_vm *vm, int n);
int					find_available_number(t_vm *vm);
void				add_champion(t_vm *vm, int n_is_set,
									int n, char *file_name);

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
void				op_sub(t_thread *pc);
void				op_and(t_thread *pc);
void				op_or(t_thread *pc);
void				op_xor(t_thread *pc);
void				op_zjmp(t_thread *pc);
void				op_ldi(t_thread *pc);
void				op_ldi_dir(t_thread *pc);
void				op_ldi_reg(t_thread *pc);
void				op_sti(t_thread *pc);
void				op_sti_ind(t_thread *pc);
void				op_sti_reg(t_thread *pc);
void				op_fork(t_thread *pc);
void				op_lld(t_thread *pc);
void				op_lldi(t_thread *pc);
void				op_lldi_dir(t_thread *pc);
void				op_lldi_reg(t_thread *pc);
void				op_lfork(t_thread *pc);
void				op_aff(t_thread *pc);

/*
** getters.c
*/

int					shift_loc(t_thread *pc, int shift);
unsigned char		get_byte_at(t_thread *pc, int amount);
int					get_bytes(t_thread *pc, int shift, int bytes);
int					get(t_thread *pc, int param_nbr, bool long_range);

/*
** setters.c
*/

void				set(t_thread *pc, int param_nbr, int value);
void				set_bytes(t_thread *pc, int param, int value);

/*
** params.c
*/

int					get_params(t_thread *pc, const t_op *op);
int					get_params_type(t_thread *pc, const t_op *op);
int					get_code(unsigned char byte, int number);

/*
** dump.c
*/

void				print_op(t_vm *vm, t_thread *pc, int print_value);
void				print_adv(t_vm *vm, t_thread *pc);
void				write_map(t_vm *vm);
void				dump(t_vm *vm);

/*
** cycle.c
*/

void				war_cycle(t_vm *vm);
int					find_opcode(int pc);
void				do_op(t_vm *vm, t_thread *pc);
void				manage_countdown(t_thread *pc);

/*
** check_cycles.c
*/

void				kill_process(t_vm *vm);
void				check_cycles(t_vm *vm);
void				print_winner(t_vm *vm);

/*
** other
*/

int					op_exit(t_thread *pc, int cycles, bool carry);
int					op_success(t_thread *pc, int cycles, int loc, bool carry);

/*
** verbose.c
*/

void				print_instruction_start(t_vm *vm, t_thread *pc);
void				print_instruction_continue(t_vm *vm);
void				print_str(t_vm *vm, char *s, int endl);
void				print_nbr(t_vm *vm, int i, int endl);
void				print_reg(t_vm *vm, int i, int endl);
void				print_byte(t_vm *vm, unsigned char byte, int endl);

#endif
