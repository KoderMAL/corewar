/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 16:36:08 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/05 18:17:01 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"
# include "io/openfile.h"

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
}					t_env;

void				ft_error_check(int err, char *err_msg);

#endif
