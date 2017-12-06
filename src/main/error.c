/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 16:19:23 by alalaoui          #+#    #+#             */
/*   Updated: 2017/12/05 16:24:23 by alalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft/ft.h"

void		ft_error_check(int err, char *err_msg)
{
	if (err)
	{
		write(1, err_msg, ft_strlen(err_msg));
		exit(1);
	}
}