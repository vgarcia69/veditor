#include "../../editor.h"

int	get_xview_from_x(t_line *line, int cursor_x, t_window *window)
{
	int xview;
	int	i;

	xview = 0;
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

int	get_x_from_xview(t_line *line, int cursor_xview, t_window *window)
{
	int x;
	int	current_xview;

	x = 0;
	current_xview = 0;
	while (current_xview < cursor_xview && x < line->len)
	{
		if (line->str[x] == '\t')
			current_xview += get_tabwidth(current_xview, window->tabstop);	
		else
			++current_xview;
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
