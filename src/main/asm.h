/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 16:36:08 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/08 19:04:12 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"
# include "io/openfile.h"
# include "util/clist.h"
# include "ft/ft.h"

typedef struct		s_label
{
	char			*label;
	int				offset;
	struct s_label	*next;
}					t_label;

typedef struct		command_arg
{
	t_arg_type		type;
	int				value;
}

typedef struct		s_command
{
	char			*name;
	t_command_arg	arg[4];
	int				n_arg;
}					t_command;

typedef struct		s_env
{
	t_openfile	input;
	t_openfile	output;
	t_op		op;
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

void				ft_error_check(int err, char *err_msg);

#endif
