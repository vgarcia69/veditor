
#include "../../editor.h"

static void	del_line(t_line *line, t_editor *e);

void	insert(t_editor *e, char c)
{
	t_line	*line;
	char	to_cat[2];

	to_cat[0] = c;
	to_cat[1] = 0;
	line = get_line(e, e->cursor->y);
	if (check_capacity(line, to_cat))
		realloc_line(e, line);
	line->str = ft_strinsert(line->str, to_cat, e->cursor->x);
	++e->cursor->x;
}

void	delete(t_editor *e)
{
	t_line	*line;

	line = get_line(e, e->cursor->y);
	if (e->cursor->x == 0)
	{
		del_line(line, e);
		return ;
	}
	ft_memmove(&line->str[e->cursor->x - 1], \
				&line->str[e->cursor->x], \
				ft_strlen(&line->str[e->cursor->x]) + 1);
	--e->cursor->x;
}

static void	del_line(t_line *line, t_editor *e)
{
	if (!line->prev)
		e->buf->head = e->buf->head->next;
	else
	{
		line->prev->next = line->next;
		e->cursor->x = line->prev->len;
	}
	free(line->str);
	free(line);
	--e->buf->nbr_line;
	--e->cursor->y;
}
