#include "../../../editor.h"

void	sc_go_begin_line(t_editor *e)
{
	e->sel->is_active = 0;
	e->cursor->x = 0;
}

void	sc_go_end_line(t_editor *e)
{
	t_line *line;

	e->sel->is_active = 0;
	line = get_line(e, e->cursor->y);
	e->cursor->x = line->len - 1;
}

void	sc_select_line(t_editor *e)
{
	t_line		*line;
	t_cursor	*start;
	t_cursor	*end;

	start = e->sel->start;
	end = e->sel->end;
	line = get_line(e, e->cursor->y);
	end->x = line->len;
	end->xview = get_xview_from_x(line, end->x, e->win);
	end->y = e->cursor->y;
	end->yview = e->cursor->y + 1;
	start->x = 0;
	start->xview = get_xview_from_x(line, start->x, e->win);
	start->y = e->cursor->y;
	start->yview = e->cursor->yview + 1;
	e->sel->is_active = 1;
}

void	sc_select_word(t_editor *e)
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
	while (start->x > 0 && ft_isualnum(line->str[start->x - 1]))
		--start->x;
	start->xview = get_xview_from_x(line, start->x + 1, e->win);
	start->y = e->cursor->y;
	start->yview = e->cursor->yview + 1;
	e->sel->is_active = 1;
}

void	sc_quit(t_editor *e)
{
	if (e->dirty)
	{
		update_statbar(e, "File unsaved ! Press CTRL + Q again to quit", -1);
		e->dirty = 0;
	}
	else
		quit_free_msg("Exit with Success !", 0, e);
}
