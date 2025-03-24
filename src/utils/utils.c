#include "../../editor.h"

int	get_xview_from_x(t_line *line, int cursor_x, t_window *win)
{
	int xview;
	int	i;

	xview = 0;
	i = win->start_col;
	while (i < cursor_x && i < line->len - 1)
	{
		if (line->str[i] == '\t')
			xview += get_tabwidth(xview, win->tabstop);	
		else
			++xview;
		++i;
	}
	return (xview + win->margin_left);
}

int	get_x_from_xview(t_line *line, int xview, t_window *win)
{
	int x;
	int	i_xview;

	x = 0;
	i_xview = win->margin_left;
	while (i_xview < xview && x < line->len)
	{
		if (line->str[x] == '\t')
			i_xview += get_tabwidth(i_xview, win->tabstop);	
		else
			++i_xview;
		++x;
	}
	return (x + win->start_col);
}

int get_tabwidth(int xview, int tabstop)
{
	return (tabstop - (xview % tabstop));
}

t_line	*get_line(t_editor *e, int index)
{
	t_line	*line;
	int		i;

	i = 0;
	line = e->head;
	while (i < index && line)
	{
		line = line->next;
		++i;
	}
	return (line);
}

int	get_margin(t_editor *e)
{
	int		size_len;
	int		size_nb;

	size_nb = len_int(e->nb_line);
	size_len = len_int(get_max_len(e->head) - 1) + 2;
	if (size_nb == -1 || size_len == -1)
		quit_free_msg("Alloc", 1, e);
	if (e->len_visu)
		return (size_nb + size_len + 3);
	return (size_nb + 2);
}

