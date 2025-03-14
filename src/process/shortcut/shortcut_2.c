#include "../../../editor.h"

void	go_begin_line(t_editor *e)
{
	e->cursor->x = 0;
}

void	go_end_line(t_editor *e)
{
	t_line *line;

	line = get_line(e, e->cursor->y);
	e->cursor->x = line->len - 1;
}

void	select_line(t_editor *e)
{
	t_line		*line;
	t_cursor	*start;
	t_cursor	*end;

	start = e->sel->start;
	end = e->sel->end;
	line = get_line(e, e->cursor->y);
	end->x = line->len - 1;
	end->xview = get_xview_from_x(line, end->x, e->win);
	end->y = e->cursor->y;
	end->yview = e->cursor->y + 1;
	start->x = 0;
	start->xview = get_xview_from_x(line, start->x, e->win);
	start->y = e->cursor->y;
	start->yview = e->cursor->yview + 1;
	e->sel->is_active = 1;
}

void	select_word(t_editor *e)
{
	t_line		*line;
	t_cursor	*start;
	t_cursor	*end;

	start = e->sel->start;
	end = e->sel->end;
	line = get_line(e, e->cursor->y);
	end->x = e->cursor->x;
	while (ft_isualnum(line->str[end->x]))
		++end->x;
	end->xview = get_xview_from_x(line, end->x, e->win);
	end->y = e->cursor->y;
	end->yview = e->cursor->y + 1;
	start->x = e->cursor->x;
	while (ft_isualnum(line->str[start->x - 1]))
		--start->x;
	start->xview = get_xview_from_x(line, start->x + 1, e->win);
	start->y = e->cursor->y;
	start->yview = e->cursor->yview + 1;
	e->sel->is_active = 1;
}

void	quit(t_editor *e)
{
	t_line	*line = e->head;

	while (line)
	{
		printf_fd(3, "[%s]", line->str);
		line = line->next;
	}
	quit_free_msg("Exit with Success !", 0, e);
}
