#include "../../editor.h"

static char	*add_sel_loop \
			(t_cursor start, t_cursor end, t_editor *e, char *buffer);
static char	*add_sel_char \
			(int xview, int yview, t_editor *e, char *buffer);

char	*add_buffer_selection(t_selection *sel, t_editor *e, char *buffer)
{
	if (!sel->is_active)
		return (buffer);
	if (sel->start->xview < e->win->margin_left)
		sel->start->xview = e->win->margin_left;
	buffer = add_sel_loop(*sel->start, *sel->end, e, buffer);
	return (buffer);
}


static char	*add_sel_loop \
			(t_cursor start, t_cursor end, t_editor *e, char *buffer)
{
	int			pos;
	t_line		*line;

	pos = ft_strlen(buffer);
	sprintf(buffer + pos, INVERT);
	while (!is_same_pos(&start, &end))
	{
		line = get_line(e, start.y);
		if (start.y < end.y)
		{
			while (get_x_from_xview(line, start.xview, e->win) < line->len)
				buffer = add_sel_char(start.xview++, start.yview, e, buffer);
			start.xview = e->win->margin_left;
			++start.yview;
			++start.y;
		}
		else
		{
			while (start.xview < end.xview + 1)
				buffer = add_sel_char(start.xview++, start.yview, e, buffer);
			break ;
		}
	}
	pos = ft_strlen(buffer);
	sprintf(buffer + pos, RESET);
	return (buffer);
}

static char	*add_sel_char \
			(int xview, int yview, t_editor *e, char *buffer)
{
	char	c;
	int		pos;
	int		tab_width;

	pos = ft_strlen(buffer);
	c = get_char_at(e, xview, yview);
	if (c == '\t')
	{
		tab_width = get_tabwidth(xview, e->win->tabstop);
		while (tab_width >= 0)
		{
			pos += sprintf(buffer + pos, "\033[%d;%dH ", yview, xview++);
			--tab_width;
		}
	}
	else
		pos += sprintf(buffer + pos, "\033[%d;%dH%c", yview, xview, c);
	if (xview == e->win->margin_left)
		pos += sprintf(buffer + pos, "\033[%d;%dH ", \
						yview, e->win->margin_left + 1);
	return (buffer);
}
