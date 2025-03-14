#include "../../editor.h"

static void	update_vars(t_line *line, t_cursor *cursor, t_window *window);
static void	update_scroll(t_cursor *cursor, t_line *line, \
			t_window *window, int nb_line);

void	editor_refresh_win(t_editor *e)
{
	t_line	*current;	

	current = get_line(e, e->cursor->y);
	update_scroll(e->cursor, current, e->win, e->buf->nbr_line);
	update_vars(current, e->cursor, e->win);
	printf_fd(STDOUT_FILENO, "\033[2J");
	printf_fd(STDOUT_FILENO, "\033[?25l");
	draw_window(e);
	draw_bottom(e->win->height, e->stat, e->mode, e->cmd);
	draw_cursor(e->cursor);
	draw_selection(e->sel, e);
	printf_fd(STDOUT_FILENO, "\033[?25h");
}

static void	update_vars(t_line *line, t_cursor *cursor, t_window *window)
{
	struct winsize ws;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) != -1)
	{
		window->height = ws.ws_row - 2;
		window->width = ws.ws_col;
	}
	cursor->xview = get_xview_from_x(line, cursor->x, window);
	cursor->yview = cursor->y - window->start_row;
}

static void	update_scroll(t_cursor *cursor, t_line *line, \
			t_window *window, int nb_line)
{
	if (cursor->yview + 6 > window->height \
		&& cursor->yview + 6 + window->start_row <= nb_line)	
		++window->start_row;
	else if (cursor->yview < 4 && window->start_row)
		--window->start_row;
	if (cursor->xview + 4 > window->width \
		&& window->width < line->len + cursor->xview - cursor->x)    
		++window->start_col;
	else if (cursor->xview < 4 && window->start_col)
		--window->start_col;
}
