#include "../../editor.h"

int	get_xview_from_x(t_line *line, int cursor_x, int tab_stop, int s_col)
{
	int xview;
	int	i;

	xview = 0;
	i = s_col;
	while (i < cursor_x && i < line->len - 1)
	{
		if (line->str[i] == '\t')
			xview += get_tabwidth(xview, tab_stop);	
		else
			++xview;
		++i;
	}
	return (xview);
}

int	get_x_from_xview(t_line *line, int cursor_xview, int tab_stop, int s_col)
{
	int x;
	int	current_xview;

	x = 0;
	current_xview = 0;
	while (current_xview < cursor_xview && x < line->len)
	{
		if (line->str[x] == '\t')
			current_xview += get_tabwidth(current_xview, tab_stop);	
		else
			++current_xview;
		++x;
	}
	x += s_col;
	return (x);
}

int get_tabwidth(int xview, int tab_stop)
{
	return (tab_stop - (xview % tab_stop));
}

int	tab_align_pos(int tab_stop, int current_x)
{
	return ((current_x / tab_stop + 1) * tab_stop);
}

t_line	*get_line(t_editor *e, int index)
{
	t_line	*line;
	int		i;

	i = 0;
	if (!e)
	{
		printf_fd(2,"Sqlut\n");
		return (NULL);
	}
	line = e->buf->head;
	while (i < index && line)
	{
		line = line->next;
		++i;
	}
	return (line);
}
