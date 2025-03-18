#include "../../editor.h"

static void	delete_newline(t_line *line, t_editor *e);

void	delete(t_editor *e)
{
	t_line	*line;
	int		cur_x;

	line = get_line(e, e->cursor->y);
	if (e->sel->is_active)
		delete_selection(e->sel, e);
	else if (e->cursor->xview == e->win->margin_left)
		delete_newline(line, e);
	else
	{
		cur_x = get_x_from_xview(line, e->cursor->xview, e->win);
		ft_memmove(&line->str[cur_x - 1], \
					&line->str[cur_x], \
					ft_strlen(&line->str[cur_x]) + 1);
		--e->cursor->x;
		--line->len;
	}
}

static void	delete_newline(t_line *line, t_editor *e)
{
	if (!line->prev)
		return ;
	line->prev->next = line->next;
	while (!check_capacity(line->prev, line->str))
		realloc_line(e, line->prev);
	ft_memcpy(&line->prev->str[line->prev->len - 1], \
				line->str, \
				line->len + 1);
	e->cursor->x = line->prev->len - 1;
	line->prev->len += line->len - 1;
	delete_line(e, line);
	--e->cursor->y;
}

void	delete_line(t_editor *e, t_line *line)
{
	if (e->nb_line <= 1)
	{
		line->str[0] = '\n';
		line->str[1] = 0;
		line->len = 1;
		return ;
	}
	if (line->prev)
		line->prev->next = line->next;
	else
		e->head = e->head->next;
	if (line->next)
		line->next->prev = line->prev;
	--e->nb_line;
	e->win->start_col = 0;
	free(line->str);
	free(line);
}
