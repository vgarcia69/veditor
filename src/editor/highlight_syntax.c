#include "../../editor.h"

static void	turn_on(int *on_off, t_display *buffer, t_editor *e);
static void	turn_off(int *on_off, t_display *buffer, t_editor *e);

void	update_hl(int *on_off, int coords[2], t_display *buffer, t_editor *e)
{
	t_cursor	*start;
	t_cursor	*end;

	if (!e->sel->is_active)
		return ;
	start = e->sel->start;
	end = e->sel->end;
	if (coords[1] == start->y && coords[1] == end->y \
		&& coords[0] >= start->x && coords[0] < end->x)
		turn_on(on_off, buffer, e);
	else if (coords[1] > start->y && coords[1] < end->y)
		turn_on(on_off, buffer, e);
	else if (coords[1] == start->y && start->x <= coords[0] \
		&& start->y != end->y)
		turn_on(on_off, buffer, e);
	else if (coords[1] == end->y && end->x > coords[0] \
		&& start->y != end->y)
		turn_on(on_off, buffer, e);
	else
		turn_off(on_off, buffer, e);
}

static void	turn_on(int *on_off, t_display *buffer, t_editor *e)
{
	if (*on_off == 0)
	{
		append_string(buffer, e, INVERT);
		*on_off = 1;
	}
}

static void	turn_off(int *on_off, t_display *buffer, t_editor *e)
{
	if (*on_off == 1)
	{
		append_string(buffer, e, RESET);
		*on_off = 0;
	}
}
/*
Si c est entre starty et endy full color.
Si c est starty -> si >= startx
Si c est endy -> si < endx
*/
