/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 23:04:41 by stoupin           #+#    #+#             */
/*   Updated: 2018/02/08 11:43:51 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "gui.h"
#include "font.h"

int		font_err(t_font *font, char *msg)
{
	font->err = 1;
	font->err_msg = msg;
	return (1);
}

int		font_load_arrays(t_font *font, int fd)
{
	int	size;
	int	ret;

	font->char_list = (char*)malloc(sizeof(char) * font->char_count);
	if (font->char_list == NULL)
		return (font_err(font, "memory error (1)"));
	if ((ret = read(fd, font->char_list, font->char_count)) != font->char_count)
		return (font_err(font, "error while reading font (5)"));
	size = font->char_count * font->char_width * font->char_height;
	if (font->grayscale == 0)
		size *= 3;
	font->pixels = (unsigned char*)malloc(sizeof(unsigned char) * size);
	if (font->pixels == NULL)
		return (font_err(font, "memory error (2)"));
	if ((ret = read(fd, font->pixels, size)) != size)
		return (font_err(font, "error while reading font (6)"));
	return (0);
}

int		font_load(t_font *font, const char *file_name)
{
	int	fd;
	int	ret;

	font->err = 0;
	font->err_msg = NULL;
	font->char_list = NULL;
	font->pixels = NULL;
	if ((fd = open(file_name, O_RDONLY)) < 0)
		return (font_err(font, "unable to open font file"));
	if ((ret = read(fd, &(font->char_count), 1)) != 1)
		return (font_err(font, "error while reading font (1)"));
	if ((ret = read(fd, &(font->char_width), 1)) != 1)
		return (font_err(font, "error while reading font (2)"));
	if ((ret = read(fd, &(font->char_height), 1)) != 1)
		return (font_err(font, "error while reading font (3)"));
	if ((ret = read(fd, &(font->grayscale), 1)) != 1)
		return (font_err(font, "error while reading font (4)"));
	font_load_arrays(font, fd);
	if (fd >= 0)
	{
		close(fd);
		fd = 0;
	}
	return (0);
}

void	font_clean(t_font *font)
{
	font->char_count = 0;
	if (font->char_list)
		free(font->char_list);
	if (font->pixels)
		free(font->pixels);
}

int		font_get_ichar(t_font *font, char c)
{
	int	i_char;

	i_char = 0;
	while (i_char < font->char_count)
	{
		if (font->char_list[i_char] == c)
			return (i_char);
		i_char++;
	}
	return (-1);
}
