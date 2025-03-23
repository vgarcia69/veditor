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
	int	xview_scol;

	x = 0;
	xview_scol = get_xview_from_x(line, win->start_col, win);
	i_xview = win->margin_left + xview_scol; 
	while (i_xview < xview + xview_scol && x < line->len)
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

int	tab_align_pos(int tabstop, int current_x)
{
	return ((current_x / tabstop + 1) * tabstop);
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
