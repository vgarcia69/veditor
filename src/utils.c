#include "../editor.h"

int	get_xview_from_x(t_line *line, int cursor_x, int tab_stop)
{
	int xview;
	int	i;

	xview = 0;
	i = 0;
	while (i < cursor_x && i < line->len)
	{
		if (line->str[i] == '\t')
			xview += get_tabwidth(xview, tab_stop);	
		else
			++xview;
		++i;
	}
	return (xview);
}

int	get_x_from_xview(t_line *line, int cursor_xview, int tab_stop)
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
	return (x);
}
/*
	pour win_x calculer win_size avec getxviewfromx
	ensuite drawline
	comment update toute les donnees ?
	scroll etc.
*/
void	draw_line(t_editor *e)
{
	int		tab_i;
	int		view_i;
	char	*str;

	str = e->buf->line->str;
	tab_i = 0;
	view_i = 0;
	str += e->win->starting_col;
	while (*str && view_i < e->win->width)
	{
		if (*str == '\t')
		{
			tab_i = get_tabwidth(view_i, e->tab_stop);
			while (tab_i-- && view_i < e->win->width)
				view_i += ft_writechar(' ', STDOUT_FILENO);
		}
		else
			view_i += ft_writechar(*str, STDOUT_FILENO);
		++str;
	}
}

int get_tabwidth(int xview, int tab_stop)
{
	return (tab_stop - (xview % tab_stop));
}

int	tab_align_pos(int tab_stop, int current_x)
{
	return ((current_x / tab_stop + 1) * tab_stop);
}
