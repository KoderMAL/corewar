/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <alalaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 14:44:18 by alalaoui          #+#    #+#             */
/*   Updated: 2018/01/17 15:18:28 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

#include "main/op.h"
#include "io/openfile.h"
#include "ft/ft.h"

typedef struct		s_thread
{
	int			carry;
	int			reg1;
	int			reg2;
	int			reg3;
	int			location;
}

typedef struct		s_champ
{
	char		name[CHAMP_MAX_SIZE];
}					t_champ

typedef struct		s_vm
{
	t_openfile		openfile;
	t_champ			champs_fd[4];
	char			map[MEM_SIZE];
	t_pqueue		threads;
	int				nb_champs;
	int				err;
	char			*err_msg;
}					t_vm;

void 	fill_map();

#endif