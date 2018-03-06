#include "gui.h"

void	draw_horizontal_line(t_gui *gui, t_coord a, int width, t_pix color)
{
	int	i;
	
	i = 0;
	while (i < width)
	{
		gui->image[a.y * gui->screen_size.x + a.x + i] = color; 
		i++;
	}
}

void	draw_vertical_line(t_gui *gui, t_coord a, int height, t_pix color)
{
	int i;
	i = 0;
	while (i < height)
	{
		gui->image[(a.y + i) * gui->screen_size.x + a.x] = color;
		i++;
	}
}

void	draw_rectangle(t_gui *gui, t_coord top_left, t_coord dim, t_pix color)
{
	draw_horizontal_line(gui, top_left, dim.x, color);
	draw_horizontal_line(gui, (t_coord){top_left.x, top_left.y + dim.y}, dim.x, color);
	draw_vertical_line(gui, top_left, dim.y, color);
	draw_vertical_line(gui, (t_coord){top_left.x + dim.x, top_left.y}, dim.y, color);
}
