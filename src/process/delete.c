
#include "../../editor.h"

static void	delete_newline(t_line *line, t_editor *e);

void	delete(t_editor *e)
{
	t_line	*line;
	int		cur_x;

	if (e->sel->is_active)
		delete_selection(e->sel, e);
	line = get_line(e, e->cursor->y);
	if (e->cursor->xview == 0)
	{
		delete_newline(line, e);
		return ;
	}
	cur_x = get_x_from_xview(line, e->cursor->xview, e->win);
	ft_memmove(&line->str[cur_x - 1], \
				&line->str[cur_x], \
				ft_strlen(&line->str[cur_x]) + 1);
	--e->cursor->x;
	--line->len;
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
	line->prev->len += line->len;
	free(line->str);
	free(line);
	--e->nbr_line;
	--e->cursor->y;
}

void	delete_line(t_editor *e)
{
	t_line	*temp;
	t_line	*line;

	line = get_line(e, e->cursor->y);
	if (line->len == 1 && e->nb_line == 0)
		return ;
	if (line->prev)
		line->prev->next = line->next;
	else
		e->head = e->head->next;
	if (line->next)
		line->next->prev = line->prev;
	else
		--e->cursor->y;
	free(line->str);
	free(line);
	--e->nb_line;
	if (e->nb_line == 0)
		create_empty_buffer(e);
}

void	delete_selection(t_selection *sel, t_editor *e)
{
	t_line	*n_line;
	char	*str;

	sel->is_active = 0;
	n_line = new_line(str);	
}

