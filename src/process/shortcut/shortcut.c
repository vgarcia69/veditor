#include "../../../editor.h"

void	sc_save(t_editor *e)
{

}

void	sc_copy(t_editor *e)
{
	t_cursor	*start;
	t_cursor	*end;

	if (!e->sel->is_active)
		return ;
	clear_cpy(e->cpy);
	start = e->sel->start;	
	end = e->sel->end;
	if (!is_ordered(start, end))
		ft_revptr((void **)start, (void **)end);
	if (start->y == end->y)
	{
		cpy_single(start->x, end->x, start->y, e);
		e->cpy->type = SINGLE;
	}
	else
	{
		cpy_first(start, e);
		cpy_mid(start, end, e);
		cpy_last(end, e);
		e->cpy->type = MULTI;
	}
	///////////////////////////////////////
	t_line *line;
	line = e->cpy->head;
	while (line)
	{
		printf_fd(4, "%s", line->str);
		line = line->next;
	}
	////////////////////////////////////////
}

void	sc_paste(t_editor *e)
{

}

void	sc_delete_line(t_editor *e)
{
	t_line	*line;

	if (e->sel->is_active)
	{
		delete_selection(e->sel, e);
		return ;
	}
	line = get_line(e, e->cursor->y);
	delete_line(e, line);
}
