/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_assoc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 11:54:44 by stoupin           #+#    #+#             */
/*   Updated: 2018/02/16 15:51:15 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_ASSOC_H
# define OP_ASSOC_H

# include "vm.h"

typedef	struct	s_op_assoc
{
	int		opcode;
	void	(*op_function)(t_thread *process);
}				t_op_assoc;

#endif
