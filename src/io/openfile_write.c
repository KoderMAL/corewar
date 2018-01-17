/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfile_write.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 13:44:43 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/17 11:29:10 by stoupin          ###   ########.fr       */
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

static void	openfile_write_digits(t_openfile *of, int n)
{
	char digit;

	if (n == 0)
		return ;
	openfile_write_digits(of, n / 10);
	if (n >= 0)
		digit = ('0' + (n % 10));
	else
		digit = ('0' - (n % 10));
	openfile_write_char(of, digit);
}

void		openfile_write_nbr(t_openfile *of, int n, int endl)
{
	if (n < 0)
		openfile_write_char(of, '-');
	if (n == 0)
		openfile_write_char(of, '0');
	else
		openfile_write_digits(of, n);
	if (endl)
		openfile_write_char(of, '\n');
}
