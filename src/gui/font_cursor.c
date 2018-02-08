/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 17:43:13 by stoupin           #+#    #+#             */
/*   Updated: 2018/02/08 11:44:00 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"

void	font_cursor_init(t_font_cursor *fc, t_font *font, t_coord c0,
							int inter_line)
{
	fc->font = font;
	fc->c0 = c0;
	fc->c = c0;
	fc->inter_line = inter_line;
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

void	font_print_char(t_gui *gui, t_font *font, t_coord c0, int i_char)
{
	t_coord	c;
	int		i;

	c = (t_coord){0, 0};
	while (c.y < font->char_height)
	{
		c.x = 0;
		while (c.x < font->char_width)
		{
			i = (c0.y + c.y) * gui->screen_size.x + (c0.x + c.x);
			if (c0.x + c.x >= 0 && c0.x + c.x < gui->screen_size.x
				&& c0.y + c.y >= 0 && c0.y + c.y < gui->screen_size.y)
				gui->image[i] = font_get_pixel(font, i_char, c);
			c.x++;
		}
		c.y++;
	}
}

void	font_cursor_print(t_gui *gui, t_font_cursor *fc, char *s)
{
	int		i_char;

	while (*s != '\0')
	{
		if (*s == '\n')
		{
			fc->c.x = fc->c0.x;
			fc->c.y += fc->font->char_height + fc->inter_line;
		}
		else
		{
			i_char = font_get_ichar(fc->font, *s);
			if (i_char >= 0)
			{
				font_print_char(gui, fc->font, fc->c, i_char);
				fc->c.x += fc->font->char_width;
			}
			else if (*s == ' ')
				fc->c.x += fc->font->char_width;
		}
		s++;
	}
}
