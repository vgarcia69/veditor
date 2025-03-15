#include "../../editor.h"

int	is_same_pos(t_cursor *p1, t_cursor *p2)
{
	if (p1->xview == p2->xview && p1->yview == p2->yview)
		return (1);
	return (0);
}

void	cp_cursor(t_cursor *dst, t_cursor *src)
{
	dst->xview = src->xview;
	dst->yview = src->yview;
	dst->x = src->x;
	dst->y= src->y;
}

int	is_ordered(t_cursor *first, t_cursor *last)
{
	if (first->yview == last->yview)
	{
		if (first->xview < last->xview)
			return (1);
	}
	else if (first->yview < last->yview)
		return (1);
	return (0);
}

char	get_char_at(t_editor *e, int xview, int yview)
{
	t_line	*line;
	int		c_index;
	char	c;

	line = get_line(e, yview + e->win->start_row - 1);
	c_index = get_x_from_xview(line, xview, e->win) - 1;
	if (c_index >= line->len - 1 || c_index < 0)
		return (0);
	c = line->str[c_index];
	return (c);
}

void	draw_line(t_editor *e, t_line *line)
{
	int		tab_i;
	int		view_i;
	char	*str;

	str = line->str;
	tab_i = 0;
	view_i = 0;
	if ((int)ft_strlen(str) < e->win->start_col)
		return ;
	str += e->win->start_col;
	while (*str && view_i < e->win->width)
	{
		if (*str == '\t')
		{
			tab_i = get_tabwidth(view_i, e->win->tabstop);
			while (tab_i-- && view_i < e->win->width)
				view_i += ft_writechar(' ', STDOUT_FILENO);
		}
		else
			view_i += ft_writechar(*str, STDOUT_FILENO);
		++str;
	}
}
