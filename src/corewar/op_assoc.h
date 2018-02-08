/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_assoc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 11:54:44 by stoupin           #+#    #+#             */
/*   Updated: 2018/02/08 12:01:08 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_ASSOC_H
# define OP_ASSOC_H

# include "vm.h"

typedef	struct	s_op_assoc
{
	int		opcode;
	int		(*op_function)(t_vm *vm, t_thread *process);
}				t_op_assoc;

#endif
