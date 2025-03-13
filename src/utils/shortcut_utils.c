#include "../../editor.h"

static void	set_start_end(t_cursor *pp, t_cursor *ip, t_cursor **s, t_cursor **e);

void	highlight(t_editor *e, t_cursor *pp, t_cursor *ip)
{
	t_cursor	*start;
	t_cursor	*end;
	t_line		*line;

	start = NULL;
	end = NULL;
	printf_fd(STDOUT_FILENO, "\033[7m");
	set_start_end(pp, ip, &start, &end);
	while (!is_same_pos(start, end))
	{
		line = get_line(e, start->y);
		if (start->y != end->y)
		{
			start->yview = start->y - e->win->start_row;
			while (start->xview < line->len)
				printf_fd(STDOUT_FILENO, "\033[%d;%dH", start->yview, ++start->xview);
			++start->y;
		}
		else
		{
			start->yview = start->y - e->win->start_row;
			while (start->xview < end->xview)
				printf_fd(STDOUT_FILENO, "\033[%d;%dH", start->yview + 1, ++start->xview);
		}
		printf_fd("[%d][%d]|[%d][%d] - [%d][%d]|[%d][%d]\n", start->xview, start->yview, start->x, start->y, end->xview, end->yview, start->x, start->y);
	}
	printf_fd(STDOUT_FILENO, "\033[0m");
}
// highlight de pp a ip;

static void	set_start_end(t_cursor *pp, t_cursor *ip, t_cursor **s, t_cursor **e)
{
	if (ip->yview == pp->yview)
	{
		if (ip->xview < pp->xview)
		{
			*s = ip;
			*e = pp;
		}
		else
		{
			*s = ip;
			*e = pp;
		}
	}
	if (ip->yview < pp->yview)
	{
		*s = ip;
		*e = pp;
	}
	else
	{
		*s = pp;
		*e = ip;
	}
}
