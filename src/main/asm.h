/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 16:36:08 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/23 16:16:40 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <stdbool.h>
# include "op.h"
# include "io/openfile.h"
# include "util/cqueue.h"
# include "util/pqueue.h"
# include "ft/ft.h"
# include "hash/crc32.h"

typedef struct		s_label
{
	bool			is_lab;
	char			*name;
	int				len; //is it used?
	int				location;
}					t_label;

typedef struct		s_gap
{
	char			*name;
	int				location;
	int				command_location;
	int				size;
	t_label			*label;
}					t_gap;

typedef struct		s_argument
{
	char			*name;
	int				type;
	int				lab_type;
	int				value;
	t_label			*label;
	int				line;
	int				col;
}					t_argument;

typedef struct		s_instruction
{
	bool			is_lab;
	const t_op		*op;
	int				len;
	t_argument		arguments[MAX_ARGS_NUMBER];
}					t_instruction;

typedef struct		s_env
{
	t_openfile		input;
	t_openfile		stdout;
	t_openfile		stderr;
	t_hash_env		hash_env;
	int				line;
	int				col;
	int				err;
	char			*err_msg;
	int				header;
	int				name_check;
	int				comment_check;
	char			*file_name;
	char			name[PROG_NAME_LENGTH];
	char			comment[COMMENT_LENGTH];
	unsigned char	*champion;
	int				prog_size;
	void			(*state)(struct s_env *env, char c);
	t_cqueue		characters;
	size_t			pos;
	const t_op		*op;
	t_pqueue		labels;
	t_pqueue		instructions;
	t_instruction	instruction;
}					t_env;

/*
** from error.c
*/

int					err(t_env *env, char *s, int col_back);
int					err_display(t_env *env);

/*
** from argument.c
*/

int					arg_from_cqueue(t_cqueue *cqueue, t_argument *argument);
void				argument_clean(t_argument *argument);

/*
** from label.c
*/

t_label				*label_from_cqueue(t_cqueue *cqueue);
t_label				*label_dup(t_label *label);

/*
** from instruction.c
*/

void				instruction_init(t_instruction *instruction,
										const t_op *op);
void				instruction_move(t_instruction *src, t_instruction *dest);
void				instruction_clean(t_instruction *instruction);

/*
** from check_args.c
*/

int					find_label(t_argument *arg, t_pqueue *labels);
void				check_argument(t_argument *arg, t_env *env);

/*
** from make_cor.c
*/

void				write_cor(t_env *env);

//from space

void				assemble(t_env *env);

#endif
