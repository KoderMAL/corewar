/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lramirez <lramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 17:04:51 by lramirez          #+#    #+#             */
/*   Updated: 2018/02/16 17:08:18 by lramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			get(t_thread *pc, int param_nbr)
{
	int		type;
	int		param;
	
	type = pc->params_type[param_nbr];
	param = pc->params[param_nbr];
	if (type == T_REG)
		return (pc->r[param])
	else if (type == T_DIR)
		return (param);
	else if (type == T_IND)
		return (pc->vm->map[param]);
}
