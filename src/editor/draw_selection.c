#include "../../editor.h"

static void	draw_loop_selection(t_cursor start, t_cursor end, t_editor *e);

void	draw_selection(t_selection *sel, t_editor *e)
{
	if (!sel->is_active)
		return ;
	if (!is_ordered(sel->start, sel->end))
		ft_revptr((void **)&sel->start, (void **)&sel->end);	
	draw_loop_selection(*sel->start, *sel->end, e);
}

static void	draw_char_selection(int xview, int yview, t_editor *e);

static void	draw_loop_selection(t_cursor start, t_cursor end, t_editor *e)
{
	t_line		*line;

	printf_fd(STDOUT_FILENO, "\033[7m");
	while (!is_same_pos(&start, &end))
	{
		line = get_line(e, start.y);
		if (start.y < end.y)
		{
			while (get_x_from_xview(line, start.xview, e->win) < line->len)
				draw_char_selection(start.xview++, start.yview, e);
			start.xview = 0;
			++start.yview;
			++start.y;
		}
		else
		{
			while (start.xview < end.xview)
				draw_char_selection(start.xview++, start.yview, e);
			break ;
		}
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
