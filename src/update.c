#include "../editor.h"

static void	update_height \
			(t_window *win, int nb_line, t_cursor *cursor, t_action *action);

void	update_statbar(t_editor *e, char *str)
{
	int	f_len;
	int	str_len;

	f_len = ft_strlen(e->f_name);
	str_len = ft_strlen(str);
	ft_memset(e->stat, ' ', e->win->width);
	if (e->mode == INSERT)
		ft_memcpy(e->stat, INSERT_TEXT, 13);
	else
		ft_memcpy(e->stat, COMMAND_TEXT, 14);
	if (f_len > 0)
		ft_memcpy(&e->stat[e->win->width - (f_len + 1)], e->f_name, f_len);
	else
		ft_memcpy(&e->stat[e->win->width - 6], "[NEW]", 5);
	if (str)
		ft_memcpy(&e->stat[e->win->width / 2 - str_len / 2], str, str_len);
}

void update_win(t_editor *e)
{
	t_line	*line;

	line = get_line(e, e->cursor->y);
	e->cursor->xview = get_xview_from_x(line, e->cursor->x, e->win);
	e->cursor->yview = e->cursor->y - e->win->start_row;
	update_height(e->win, e->nb_line, e->cursor, &e->act);	
	update_width(e->win, e->cursor, e);	
	update_vars(e->cursor, e->win, e);
}

static void	update_height \
			(t_window *win, int nb_line, t_cursor *cursor, t_action *action)
{
    int		target_row;
	int		prev_startrow;
	int		pad;

	pad = 4;
	prev_startrow = win->start_row;
	if (cursor->yview + pad > win->height - 2)
    {
        target_row = cursor->y - (win->height - 2 - pad);
        if (target_row > nb_line - win->height + 2)
            target_row = nb_line - win->height + 2;
        win->start_row = target_row;
    }
    else if (cursor->yview < pad)
    {
        target_row = cursor->y - pad;
        win->start_row = target_row;
    }
	if (win->start_row < 0)
		win->start_row = 0;
	if (prev_startrow != win->start_row)
		*action = T_MULTI;
}

void	update_width(t_window *win, t_cursor *cursor, t_editor *e)
{
	t_line	*line;
	int		target_col;
	int		pad;
	int		prev_startcol;

	pad = 4;
	prev_startcol = win->start_col;
	line = get_line(e, cursor->y);
	if (line->len - win->start_col < win->width - win->margin_left - pad * 2)
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
	if (prev_startcol != win->start_col)	
		e->act = T_MULTI;
}

void	update_vars(t_cursor *cursor, t_window *win, t_editor *e)
{
	t_line	*line;

	line = get_line(e, e->cursor->y);
	e->win->margin_left = get_margin(e, e->opt);
	cursor->xview = get_xview_from_x(line, cursor->x, win);
	cursor->yview = cursor->y - win->start_row;
}
