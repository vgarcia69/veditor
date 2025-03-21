#include "../../editor.h"

static char	*add_tild(int i, int height, char *buffer);
static char	*fill_border(t_editor *e, t_line *line, int i, char *buf);

char	*add_buffer_window(t_editor *e, char *buffer)
{
	char	*line_buf;
	int		i;
	t_line	*line;

	i = 0;
	line = get_line(e, e->win->start_row);
	while (line && i < e->win->height)
	{
		buffer = fill_border(e, line, ++i, buffer);
		line_buf = buffer_line(e, line);
		if (line_buf == NULL)
		{
			free(buffer);
			quit_free_msg("Alloc", 1, e);
		}
		buffer = ft_strcat(buffer, line_buf);
		free(line_buf);
		line = line->next;
	}
	buffer = add_tild(i + 1, e->win->height + 1, buffer);
	return (buffer);
}

static char	*fill_border(t_editor *e, t_line *line, int i, char *buf)
{
	int	x_viewi;
	int	x_viewlen;
	int	margin;
	int	max_len;
	int	pos;

	pos = ft_strlen(buf);
	max_len = 0;
	if (e->len_visu)
		max_len = len_int(get_max_len(e->head) - 1);
	if (max_len == -1)
		quit_free_msg("Alloc", 1, e);
	margin = get_margin(e);
	x_viewi = margin - \
		len_int(i + e->win->start_row) - max_len-e->len_visu * 3;
	x_viewlen = margin - len_int(line->len - 1) - 2;
	pos += sprintf(buf + pos, "\033[%d;%dH", i, x_viewi);
	pos += sprintf(buf + pos, YELLOW"%d"RESET, i + e->win->start_row);
	if (e->len_visu)
	{
		pos += sprintf(buf + pos, "\033[%d;%dH", i, x_viewlen);
		pos += sprintf(buf + pos, "["BLUE"%d"RESET"]", line->len - 1);
	}
	pos += sprintf(buf + pos, "\033[%d;%dH", i, margin + 1);
	return (buf);
}

static char	*add_tild(int i, int height, char *buffer)
{
	int	pos;

	pos = ft_strlen(buffer);
	while (i < height)
	{
	  	pos += sprintf(buffer + pos, "\033[%d;1H", i);
		pos += sprintf(buffer + pos, BLUE"~"RESET);
		i++;
	}
	return (buffer);
}
