#include "../../editor.h"

static void	update_vars(t_editor *e, t_line *line);
static void	update_scroll(t_editor *e, t_line *line);
static void	draw_selection(t_selection *sel, t_editor *e);

void	editor_refresh_win(t_editor *e)
{
	t_line	*current;	

	current = get_line(e, e->cursor->y);
	update_scroll(e, current);
	update_vars(e, current);
	printf_fd(STDOUT_FILENO, "\033[2J");
	printf_fd(STDOUT_FILENO, "\033[?25l");
	draw_window(e);
	draw_bottom(e->win->height, e->stat, e->mode, e->cmd);
	draw_selection(e->sel, e);
	draw_cursor(e->cursor);
	printf_fd(STDOUT_FILENO, "\033[?25h");
}

static void	update_vars(t_editor *e, t_line *line)
{
	struct winsize ws;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) != -1)
	{
		e->win->height = ws.ws_row - 2;
		e->win->width = ws.ws_col;
	}
	e->cursor->xview = get_xview_from_x(line, e->cursor->x, \
				e->tabstop, e->win->start_col);
	e->cursor->yview = e->cursor->y - e->win->start_row;
}

static void	update_scroll(t_editor *e, t_line *line)
{
	if (e->cursor->yview + 6 > e->win->height \
		&& e->cursor->yview + 6 + e->win->start_row <= e->buf->nbr_line)	
	{
		++e->win->start_row;
	}
	else if (e->cursor->yview < 4 && e->win->start_row)
	{
		--e->win->start_row;
	}
	if (e->cursor->xview + 4 > e->win->width \
        && e->win->width < line->len + e->cursor->xview - e->cursor->x)    
    {
        ++e->win->start_col;
    }
    else if (e->cursor->xview < 4 && e->win->start_col)
    {
        --e->win->start_col;
    }
}

static void	draw_selection(t_selection *sel, t_editor *e)
{
	t_cursor	*temp;
	t_line		*line;

	if (!sel->is_active)
		return ;
	if (!is_ordered(sel->start, sel->end))
	{
		temp = sel->start;
		sel->start = sel->end;
		sel->end = temp;
	}
	while (!is_same_pos(sel->start, sel->end))
	{
		printf_fd(STDOUT_FILENO, "\033[7m");
		line = get_line(e, sel->start->y);
		if (sel->start->yview < sel->end->yview)
		{
			while (get_x_from_xview(line, sel->start->xview, e->tabstop, e->win->start_col) < line->len)
				printf_fd(STDOUT_FILENO, "\033[%d;%dH", sel->start->yview, ++sel->start->xview);
			sel->start->xview = 0;
			++sel->start->yview;
		}
		else
			while (sel->start->xview < sel->end->xview)
				printf_fd(STDOUT_FILENO, "\033[%d;%dH", sel->start->yview + 1, ++sel->start->xview);
		printf_fd(3,"[%d][%d]|[%d][%d] - [%d][%d]|[%d][%d]\n", sel->start->xview, sel->start->yview, sel->start->x, sel->start->y, sel->end->xview, sel->end->yview, sel->start->x, sel->start->y);
		printf_fd(STDOUT_FILENO, "\033[0m");
	}
}
