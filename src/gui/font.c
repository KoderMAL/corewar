/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 23:04:41 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/29 11:48:36 by stoupin          ###   ########.fr       */
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

int		font_load(t_font *font, const char *file_name)
{
	int	fd;
	int	ret;
	int	size;

	font->err = 0;
	font->err_msg = NULL;
	font->char_list = NULL;
	font->pixels = NULL;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (font_err(font, "unable to open font file"));
	ret = read(fd, &(font->char_count), 1);
	if (ret != 1)
		return (font_err(font, "error while reading font (1)"));
	ret = read(fd, &(font->char_width), 1);
	if (ret != 1)
		return (font_err(font, "error while reading font (2)"));
	ret = read(fd, &(font->char_height), 1);
	if (ret != 1)
		return (font_err(font, "error while reading font (3)"));
	ret = read(fd, &(font->grayscale), 1);
	if (ret != 1)
		return (font_err(font, "error while reading font (4)"));
	font->char_list = (char*)malloc(sizeof(char) * font->char_count);
	if (font->char_list == NULL)
		return (font_err(font, "memory error (1)"));
	ret = read(fd, font->char_list, font->char_count);
	if (ret != font->char_count)
		return (font_err(font, "error while reading font (5)"));
	size = font->char_count * font->char_width * font->char_height;
	if (font->grayscale == 0)
		size *= 3;
	font->pixels = (unsigned char*)malloc(sizeof(unsigned char) * size);
	if (font->pixels == NULL)
		return (font_err(font, "memory error (2)"));
	ret = read(fd, font->pixels, size);
	if (ret != size)
		return (font_err(font, "error while reading font (6)"));
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

t_pix	font_get_pixel(t_font *font, int i_char, t_coord c)
{
	int				char_size;
	int				pixel_size;
	unsigned char	*p;
	t_pix			pix;

	pixel_size = (font->grayscale) ? 1 : 3;
	char_size = font->char_width * font->char_height * pixel_size;
	p = font->pixels + i_char * char_size
		 + (c.y * font->char_width + c.x) * pixel_size;
	if (font->grayscale == 0)
	{
		pix.c.r = *p++;
		pix.c.g = *p++;
		pix.c.b = *p++;
	}
	else
	{
		pix.c.r = *p;
		pix.c.g = *p;
		pix.c.b = *p;
	}
	pix.c.a = 0;
	return (pix);
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
