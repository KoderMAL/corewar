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
# include "ft/ft.h"

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
	struct s_args	*next;
}					t_args;

typedef struct		s_command
{
	char			*name;
	const t_op		*op;
	struct s_args	args;
	int				n_arg;
}					t_command;

typedef struct		s_env
{
	t_openfile	input;
	t_openfile	stdout;
	t_openfile	stderr;
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
	t_cqueue		cqueue;
	int			reread;
	t_label		*labels;
	t_command	*commands;
	const t_op	*op;
	int			offset;
}					t_env;

/*
** from error.c
*/

int					err(t_env *env, char *s);
int					err_display(t_env *env);

/*
** from record_label.c
*/

t_label				*init_label(t_env *env);
void				record_label(t_env *env);
int					ft_cqueue_cmp(char *name, t_cqueue *cqueue);
const t_op			*find_op(t_env *env);

#endif
