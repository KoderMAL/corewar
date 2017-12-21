/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 16:36:08 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/19 15:47:28 by alalaoui         ###   ########.fr       */
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

typedef struct		s_args
{
	int				type;
	char			value[4];
}					t_args;

typedef struct		s_instruction
{
	char			*name;
	const t_op		*op;
	t_pqueue		args;
}					t_instructions;

typedef struct		s_env
{
	t_openfile	input;
	t_openfile	stdout;
	t_openfile	stderr;
	int			line;
	int			col;
	int			err;
	char		*err_msg;
	int			header;
	char		name[PROG_NAME_LENGTH];
	char		comment[COMMENT_LENGTH];
	void		(*state)(struct s_env *env, char c);
	t_cqueue	characters;
	size_t		pos;
	const t_op	*op;
	t_pqueue	labels;
	t_pqueue	instructions;
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

#endif
