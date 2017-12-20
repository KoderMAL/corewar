/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfile_write.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 13:44:43 by stoupin           #+#    #+#             */
/*   Updated: 2017/12/05 14:32:13 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openfile.h"

void		openfile_write_str(t_openfile *of, char *s, int endl)
{
    while (*s != '\0')
        openfile_write_char(of, *s++);
    if (endl)
        openfile_write_char(of, '\n');
}
