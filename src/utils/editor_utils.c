#include "../../editor.h"

char	*buffer_line(t_editor *e, t_line *line)
{
	char	*buffer;
	char	*str;

	buffer = ft_calloc(sizeof(char), (line->len + 1) * 2);
	if (!buffer)
		return (NULL);	
	if (line->len <= e->win->start_col + 1)
	{
		buffer[0] = ' ';
		return (buffer);
	}
	str = line->str;
	str += e->win->start_col;
	buffer = fill_line_buffer(str, buffer, e->win);
	return (buffer);
}

char	*fill_line_buffer(char *str, char *buffer, t_window *win)
{
	int		tab_i;
	int		view_i;

	tab_i = 0;
	view_i = 0;
	while (*str && view_i < win->width)
	{
		if (*str == '\t')
		{
			tab_i = get_tabwidth(view_i + win->margin_left, win->tabstop);
			while (tab_i-- && view_i < win->width)
				buffer[view_i++] = ' ';
		}
		else
			buffer[view_i++] = *str;
		++str;
	}
	return (buffer);
}

char	*clear_window(t_editor *e, char *buffer)
{
	int	i;
	int	pos;

	i = 0;
	pos = ft_strlen(buffer);
	while (i <= e->win->height)
	{
		pos += snprintf(buffer + pos, 10, "\033[%dH\033[2K", i);
		++i;
	}
	return (buffer);
}
