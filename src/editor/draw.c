#include "../../editor.h"

static void	draw_tild(int i, int height);
static void	draw_border(t_editor *e, t_line *line, int i, int max_len);

void	draw_window(t_editor *e)
{
	t_line	*line;
	int		max_len;
	int		i;

	i = 0;
	line = get_line(e, e->win->start_row);
	max_len = 0;
	if (e->opt->draw_strlen)
	{
		max_len = len_int(get_max_len(e->head));
		if (max_len == -1)
			quit_free_msg("Alloc", 1, e);
	}
	while (line && i < e->win->height)
	{
		draw_border(e, line, i, max_len);
		draw_line(e, line);
		line = line->next;
		i++;
	}
	draw_tild(i + 1, e->win->height + 1);
}

static void	draw_border(t_editor *e, t_line *line, int i, int max_len)
{
	int	margin;
	int	len_len;
	int	len_nb;

	len_nb = len_int(i + 1 + e->win->start_row);
	len_len = len_int(line->len - 1);
	margin = get_margin(e, e->opt);
	printf_fd(STDOUT_FILENO, "\033[%d;%dH", i + 1, margin - (len_nb + max_len));
	printf_fd(STDOUT_FILENO, "%d", i + 1 + e->win->start_row);
	if (e->opt->draw_strlen)
	{
		printf_fd(STDOUT_FILENO, "\033[%d;%dH", i + 1, margin - len_len + 1);
		printf_fd(STDOUT_FILENO, "[%d]", line->len - 1);
	}
	printf_fd(STDOUT_FILENO, "\033[%d;%dH", i + 1, margin + 1);
}

static void	draw_tild(int i, int height)
{
	while (i < height)
	{
	  	printf_fd(STDOUT_FILENO, "\033[%d;1H", i);
		printf_fd(STDOUT_FILENO, "~");
		i++;
	}
}

void	draw_cursor(t_cursor *c)
{
	printf_fd(STDOUT_FILENO, "\033[%d;%dH", c->yview + 1, c->xview + 1);
	printf_fd(STDOUT_FILENO, "\033[7m");
	printf_fd(STDOUT_FILENO, "\033[%d;%dH", c->yview + 1, c->xview + 1);
	printf_fd(STDOUT_FILENO, "\033[0m");
}

void	draw_bottom(int height, char *stat, int mode, char *cmd)
{
	printf_fd(STDOUT_FILENO, "\033[%d;1H\033[1;7m", height + 1);
	printf_fd(STDOUT_FILENO, "%s", stat);
	printf_fd(STDOUT_FILENO, "\033[%d;1H\033[0m", height + 2);
	printf_fd(STDOUT_FILENO, "\033[%d;1H", height + 3);
	printf_fd(STDOUT_FILENO, "%s", cmd);
}
