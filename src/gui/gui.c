/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <stoupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 09:48:12 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/29 11:40:29 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx.h"
#include "font.h"
#include "gui.h"

int		gui_err(t_gui *gui, char *msg)
{
	gui->err = 1;
	gui->err_msg = msg;
	return (1);
}

int		gui_init(t_gui *gui, int width, int height, char *title)
{
	int	dum[3];

	gui->err = 0;
	gui->err_msg = NULL;
	gui->screen_size = (t_coord){width, height};
	gui->mlx_ptr = mlx_init();
	if (gui->mlx_ptr ==  NULL)
		return (gui_err(gui, "mlx initialization failed"));
	gui->mlx_win = mlx_new_window(gui->mlx_ptr, width, height, title);
	if (gui->mlx_win == NULL)
		return (gui_err(gui, "mlx window initialization failed"));
	gui->image_ptr = mlx_new_image(gui->mlx_ptr, width, height);
	if (gui->image_ptr == NULL)
		return (gui_err(gui, "image initialization failed"));
	gui->image = (t_pix*)mlx_get_data_addr(gui->image_ptr,
					dum, dum + 1, dum + 2);
	if (gui->image == NULL)
		return (gui_err(gui, "image address retrieval failed"));
	clear_image(gui->image, gui->screen_size, (t_pix)(unsigned int)0);
	return (0);
}

void	gui_clean(t_gui *gui)
{
	if (gui->image_ptr != NULL)
		mlx_destroy_image(gui->mlx_ptr, gui->image_ptr);
	if (gui->mlx_win != NULL)
		mlx_destroy_window(gui->mlx_ptr, gui->mlx_win);
}

void	clear_image(t_pix *image, t_coord size, t_pix color)
{
	int	i;

	i = 0;
	while (i < size.x * size.y)
		image[i++] = color;
}
