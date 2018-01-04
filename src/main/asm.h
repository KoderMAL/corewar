/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 16:36:08 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/04 17:04:33 by alalaoui         ###   ########.fr       */
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
	char			*name;
	size_t			len;
	int				instruction_number;
}					t_label;

typedef struct		s_argument
{
	int				type;
	int				value;
	char			*name;
	t_label			*label;
}					t_argument;

typedef struct		s_instruction
{
	const t_op		*op;
	t_pqueue		arguments;
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

t_label				*label_from_cqueue(t_cqueue *cqueue, int instruction_number);

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
