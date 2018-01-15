/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 16:36:08 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/15 15:39:27 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"
# include "io/openfile.h"
# include "util/cqueue.h"
# include "util/pqueue.h"
# include "ft/ft.h"

typedef struct		s_label
{
	int				is_lab;
	char			*name;
	size_t			len;
	int				location;
}					t_label;

typedef struct		s_argument
{
	char			*name;
	int				type;
	int				lab_type;
	int				value;
	t_label			*label;
}					t_argument;

typedef struct		s_instruction
{
	int				is_lab;
	const t_op		*op;
	int				len;
	t_argument		*arguments[4];
}					t_instruction;

typedef struct		s_env
{
	t_openfile		input;
	t_openfile		stdout;
	t_openfile		stderr;
	int				line;
	int				col;
	int				err;
	char			*err_msg;
	int				header;
	char			name[PROG_NAME_LENGTH];
	char			comment[COMMENT_LENGTH];
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
** from label.c
*/

t_label				*label_from_cqueue(t_cqueue *cqueue);
t_argument			*arg_from_cqueue(t_cqueue *cqueue);
t_label				*label_dup(t_label *label);
/*
** from instruction.c
*/

void				instruction_init(t_env *env);
t_instruction		*instruction_dup(t_instruction *instruction);

/*
** from check_args.c
*/

int					find_label(t_argument *arg, t_pqueue *labels);
void				check_argument(t_argument *arg, t_env *env);

#endif
