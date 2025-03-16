#include "../../editor.h"

int	get_xview_from_x(t_line *line, int cursor_x, t_window *window)
{
	int xview;
	int	i;

	xview = window->margin_left;
	i = window->start_col;
	while (i < cursor_x && i < line->len - 1)
	{
		if (line->str[i] == '\t')
			xview += get_tabwidth(xview, window->tabstop);	
		else
			++xview;
		++i;
	}
	return (xview);
}

int	get_x_from_xview(t_line *line, int xview, t_window *window)
{
	int x;
	int	i_xview;

	x = 0;
	i_xview = window->margin_left;
	while (i_xview < xview && x < line->len)
	{
		if (line->str[x] == '\t')
			i_xview += get_tabwidth(i_xview, window->tabstop);	
		else
			++i_xview;
		++x;
	}
	return (x + window->start_col);
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
