#include "../../editor.h"

static void	update_vars(t_editor *e, t_line *line);
static void	update_scroll(t_editor *e, t_line *line);

void	editor_refresh_win(t_editor *e)
{
	t_line	*current;	

	current = get_line(e, e->cursor->y);
	update_scroll(e, current);
	update_vars(e, current);
	printf_fd(STDOUT_FILENO, "\033[2J");
	printf_fd(STDOUT_FILENO, "\033[?25l");
	draw_window(e);
	draw_status(e->win->height, e->stat, e->mode);
	draw_command(e->win->height, e->cmd);
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
	e->cursor->xview = get_xview_from_x(line, e->cursor->x, e->tab_stop, e->win->starting_col);
	e->cursor->yview = e->cursor->y - e->win->starting_row;
}

static void	update_scroll(t_editor *e, t_line *line)
{
	if (e->cursor->yview + 4 > e->win->height - 1 \
		&& e->cursor->yview + 4 + e->win->starting_row <= e->buf->nbr_line - 1)	
	{
		++e->win->starting_row;
	}
	else if (e->cursor->yview < 4 && e->win->starting_row)
	{
		--e->win->starting_row;
	}
	if (e->cursor->xview + 4 > e->win->width \
        && e->win->width < (int)ft_strlen(line->str))    
    {
        ++e->win->starting_col;
    }
    else if (e->cursor->xview < 4 && e->win->starting_col)
    {
        --e->win->starting_col;
    }
}
