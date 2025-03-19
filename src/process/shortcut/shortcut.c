#include "../../../editor.h"

void	sc_save(t_editor *e)
{
	t_line	*line;
	int	fd;

	if (!e->f_name)
	{
		ft_memcpy(&e->stat[e->win->width / 2 - 16], \
					"Error no name, /name \"file_name\"", 32);
		return ;
	}
	fd = open(e->f_name, O_TRUNC | O_CREAT | O_WRONLY, 0777);
	if (fd == -1)
		quit_free_msg("Savefile", 1, e);
	line = e->head;
	while (line)
	{
		printf_fd(fd, "%s", line->str);
		line = line->next;
	}
	ft_memcpy(&e->stat[e->win->width / 2 - 9], "Successfully saved", 18);
	e->dirty = 0;
	close(fd);
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
	if (start->y == end->y && get_line(e, start->y)->len == end->x)
	{
		e->cpy->type = SINGLE_NODE;
		cpy_node(get_line(e, start->y), e);
	}
	else if (start->y == end->y)
	{
		e->cpy->type = SINGLE;
		cpy_single(start->x, end->x, start->y, e);
	}
	else
	{
		e->cpy->type = MULTI;
		cpy_first(start, e);
		cpy_mid(start, end, e);
		cpy_last(end, e);
	}
}

void	sc_paste(t_editor *e)
{
	t_line	*line;
	char	*carry;

	line = get_line(e, e->cursor->y);
	if (!e->cpy->nb_line)
		return ;
	e->dirty = 1;
	if (e->cpy->type == SINGLE)
		paste_single(line, e->cursor->x, e);
	else if (e->cpy->type == SINGLE_NODE)
		paste_single_node(line, e);
	else if (e->cpy->type == MULTI)
	{
		carry = paste_first(line, e->cursor->x, e);
		line = paste_mid(line, e, carry);
		paste_last(line, e, carry);
		free(carry);
	}
}

void	sc_delete_line(t_editor *e)
{
	t_line	*line;

	e->dirty = 1;
	if (e->sel->is_active)
	{
		delete_selection(e->sel, e);
		return ;
	}
	line = get_line(e, e->cursor->y);
	delete_line(e, line);
}
