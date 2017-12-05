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

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "op.h"

# define BUFF_SIZE 8

typedef struct		s_openfile
{
	int				fd;
	char			buffer[BUFF_SIZE];
	int				pos;
	int				buff_size;
}					t_openfile;

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

void				openfile_init(t_openfile *of, int fd);
int					openfile_read_char(t_openfile *of, char *c);
void				openfile_write_char(t_openfile *of, char c);
void				openfile_flush(t_openfile *of);
void				openfile_write_str(t_openfile *fd, char *str, int end);
void				openfile_write_nbr(t_openfile *fd, int *nbr, int end);

void				ft_error_check(int err, char *err_msg);

/*
**	States functions
*/

void				state_0(t_env *env, char c);
void				state_1(t_env *env, char c);
void				state_2(t_env *env, char c);
void				state_3(t_env *env, char c);
void				state_4(t_env *env, char c);
void				state_5(t_env *env, char c);
void				state_6(t_env *env, char c);
void				state_7(t_env *env, char c);
void				state_8(t_env *env, char c);
void				state_9(t_env *env, char c);

/*
** Library functions
*/

size_t				ft_strlen(const char *s);
void				ft_bzero(void *s, size_t n);

#endif
