#include "../editor.h"

void update_all(t_editor *e)
{
	update_height(e->win, e->nb_line, e->cursor);	
	update_width(e->win, e->cursor, e);	
	update_vars(e->cursor, e->win, e);
}

void	update_height(t_window *win, int nb_line, t_cursor *cursor)
{
    int target_row;
	int	pad;

	pad = 4;
	if (cursor->yview + pad > win->height - 2)
    {
        target_row = cursor->y - (win->height - 2 - pad);
        if (target_row > nb_line - win->height + 2)
            target_row = nb_line - win->height + 2;
        if (target_row < 0)
            target_row = 0;
        win->start_row = target_row;
    }
    else if (cursor->yview < pad)
    {
        target_row = cursor->y - pad;
        if (target_row < 0)
            target_row = 0;
        win->start_row = target_row;
    }
}

void	update_width(t_window *win, t_cursor *cursor, t_editor *e)
{
	t_line	*line;
	int		view_end; 
    int		target_col;
    int		pad;

	pad = 4;
	line = get_line(e, cursor->y);
	view_end = line->len - win->start_col;
    if (view_end < win->width - win->margin_left - pad * 2)
        win->start_col = line->len - (win->width - win->margin_left) + pad;
    else if (cursor->xview + pad > win->width)
    {
        target_col = cursor->x - win->margin_left - (win->width - pad);
        win->start_col = target_col + pad * 2;
    }
    else if (cursor->xview - win->margin_left < pad)
    {
        target_col = cursor->x - win->margin_left - pad;
        win->start_col = target_col;
    }
    if (win->start_col < 0)
        win->start_col = 0;
}

void	update_vars(t_cursor *cursor, t_window *win, t_editor *e)
{
	struct winsize	ws;
	t_line	*line;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) != -1)
	{
		win->height = ws.ws_row - 2;
		win->width = ws.ws_col;
	}
	line = get_line(e, e->cursor->y);
	e->win->margin_left = get_margin(e, e->opt);
	cursor->xview = get_xview_from_x(line, cursor->x, win);
	cursor->yview = cursor->y - win->start_row;
}
