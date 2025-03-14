#include "../../editor.h"

void	draw_window(t_editor *e)
{
	t_line	*line;
	int		i;

	i = 0;
	line = get_line(e, e->win->start_row);
	while (line && i < e->win->height)
	{
	  	printf_fd(STDOUT_FILENO, "\033[%d;1H", ++i);
		draw_line(e, line);
	  	// printf_fd(STDOUT_FILENO, "\033[%d;%dH[%d]", i, e->win->width - 5, line->len - 1); a mettre en option
		line = line->next;
	}
	while (i < e->win->height)
	{
	  	printf_fd(STDOUT_FILENO, "\033[%d;1H", ++i);
		printf_fd(STDOUT_FILENO, "~");
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

static void	draw_loop_selection(t_cursor start, t_cursor end, t_editor *e);

void	draw_selection(t_selection *sel, t_editor *e)
{
	t_cursor	*temp;
	t_cursor	*start;
	t_cursor	*end;

	if (!sel->is_active)
		return ;
	start = sel->start;
	end = sel->end;
	if (!is_ordered(start, end))
	{
		temp = start;
		start = end;
		end = temp;
	}
	draw_loop_selection(*start, *end, e);
}

static void	draw_char_selection(int xview, int yview, t_editor *e);

static void	draw_loop_selection(t_cursor start, t_cursor end, t_editor *e)
{
	t_line		*line;

	printf_fd(STDOUT_FILENO, "\033[7m");
	while (!is_same_pos(&start, &end))
	{
		line = get_line(e, start.y);
		if (start.yview < end.yview)
		{
			while (get_x_from_xview(line, start.xview, e->win) < line->len)
				draw_char_selection(start.xview++, start.yview, e);
			start.xview = 0;
			++start.yview;
			++start.y;
		}
		else
			while (start.xview < end.xview)
				draw_char_selection(start.xview++, start.yview, e);
	}
	printf_fd(STDOUT_FILENO, "\033[0m");
}

static void	draw_char_selection(int xview, int yview, t_editor *e)
{
	char	c;
	int		tab_width;

	c = get_char_at(e, xview, yview);
	if (c == '\t')
	{
		tab_width = get_tabwidth(xview, e->win->tabstop);
		while (tab_width >= 0)
		{
			printf_fd(STDOUT_FILENO, "\033[%d;%dH ", yview, xview++);
			--tab_width;
		}
	}
	else
		printf_fd(STDOUT_FILENO, "\033[%d;%dH%c", yview, xview, c);
	if (xview == 0)
		printf_fd(STDOUT_FILENO, "\033[%d;%dH ", yview, 1);
}
