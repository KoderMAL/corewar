/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 23:02:28 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/28 19:08:21 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FONT_H
# define FONT_H

#include "gui.h"

typedef struct	s_font
{
	unsigned char	char_count;
	unsigned char	char_width;
	unsigned char	char_height;
	unsigned char	grayscale;
	char			*char_list;
	unsigned char	*pixels;
	int				err;
	char			*err_msg;
}				t_font;

typedef struct	s_font_cursor
{
	t_font	*font;
	t_coord	c0;
	t_coord	c;
	int		inter_line;
}				t_font_cursor;

/*
** font.c
*/

int				font_load(t_font *font, char *file_name);
void			font_clean(t_font *font);
t_pix			font_get_pixel(t_font *font, int i_char, t_coord c);
int				font_get_ichar(t_font *font, char c);

/*
** font_cursor.c
*/

void			font_cursor_init(t_font_cursor *fc, t_font *font,
									t_coord c0, int inter_line);
void			font_print_char(t_gui *gui, t_font *font,
									t_coord c0, int i_char);
void			font_cursor_print(t_gui *gui, t_font_cursor *fc, char *s);

#endif
