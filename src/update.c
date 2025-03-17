#include "../editor.h"

void	update_vars(t_line *line, t_cursor *cursor, t_window *win, t_editor *e)
{
	struct winsize ws;
	int		spaces;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) != -1)
	{
		win->height = ws.ws_row - 2;
		win->width = ws.ws_col;
	}
	spaces = 3;
	e->win->margin_left = get_margin(e, e->opt) + spaces;
	cursor->xview = get_xview_from_x(line, cursor->x, win);
	cursor->yview = cursor->y - win->start_row;
}

void	update_scroll(t_cursor *cursor, t_window *window, int nb_line)
{
	int	pad;

	pad = 4;
	if (cursor->yview + pad > window->height - 2 \
		&& cursor->yview + window->start_row <= nb_line)	
		++window->start_row;
	else if (cursor->yview < pad && window->start_row)
		--window->start_row;
	if (cursor->xview + pad > window->width)
		++window->start_col;
	else if (cursor->xview - window->margin_left < pad && window->start_col)
		--window->start_col;
}
