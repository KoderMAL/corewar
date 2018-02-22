/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_assoc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 11:54:44 by stoupin           #+#    #+#             */
/*   Updated: 2018/02/21 14:57:04 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_ASSOC_H
# define OP_ASSOC_H

# include "vm.h"

typedef	struct	s_op_assoc
{
	int		opcode;
	void	(*op_function)(t_thread *process);
	int		print_as_direct;
}				t_op_assoc;

const t_op		*get_op_by_code(int pc);

#endif
