/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 21:43:22 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/29 11:49:45 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

# ifdef LINUX
#  define KEY_ESC (65307)
# else
#  define KEY_ESC (53)
# endif

typedef struct			s_coord
{
	int	x;
	int	y;
}						t_coord;

typedef union			u_pix
{
	unsigned int		i;
	struct				s_c
	{
		unsigned char	b;
		unsigned char	g;
		unsigned char	r;
		unsigned char	a;
	}					c;
}						t_pix;

typedef struct			s_gui
{
	t_coord			screen_size;
	void			*mlx_ptr;
	void			*mlx_win;
	void			*image_ptr;
	t_pix			*image;
	int				err;
	char			*err_msg;
}						t_gui;

/*
** gui.c
*/

int						gui_err(t_gui *gui, char *msg);
int						gui_init(t_gui *gui, int width, int height,
									char *title);
void					gui_clean(t_gui *gui);
void					clear_image(t_pix *image, t_coord size, t_pix color);

#endif
