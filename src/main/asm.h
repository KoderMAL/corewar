/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 16:36:08 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/13 17:56:33 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"
# include "io/openfile.h"
# include "util/clist.h"
# include "ft/ft.h"
# include "parsing/parsing.h"

typedef struct		s_label
{
	char			*label;
	int				offset;
	struct s_label	*next;
}					t_label;

typedef struct		s_args
{
	int				type;
	char			value[4];
	t_args			*next;
}					t_args;

typedef struct		s_command
{
	char			*name;
	t_op			op;
	t_args			args;
	int				n_arg;
}					t_command;

typedef struct		s_env
{
	t_openfile	input;
	t_openfile	output;
	int			line;
	int			col;
	int			err;
	char		*err_msg;
	char		name[PROG_NAME_LENGTH];
	int			name_length;
	char		comment[COMMENT_LENGTH];
	int			comment_length;
	void		(*state)(struct s_env *env, char c);
	void		(*state_next)(struct s_env *env, char c);
	t_clist		clist;
	int			reread;
	t_labels	*labels;
	t_commands	*commands;
	t_op		op;
	int			offset;
}					t_env;

void				ft_err(t_env *env, char *s);
void				ft_error_check(int err, char *err_msg);

#endif
