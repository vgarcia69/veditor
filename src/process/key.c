
#include "../../editor.h"

static void	insert_line(t_line *line, t_editor *e);
static void	del_line(t_line *line, t_editor *e);

void	insert(t_editor *e, char c)
{
	t_line	*line;
	char	to_cat[2];
	int		cur_x;

	/////
	printf_fd(2, "c[%c] %d, %d | %d, %d\n", c, e->cursor->xview, e->cursor->yview, e->cursor->x, e->cursor->y);
	/////
	line = get_line(e, e->cursor->y);
	if (c == '\r' || c == '\n')
	{
		insert_line(line, e);
		return ;
	}
	to_cat[0] = c;
	to_cat[1] = 0;
	while (!check_capacity(line, to_cat))
		realloc_line(e, line);
	cur_x = e->cursor->x;
	if (e->cursor->x > e->cursor->xview)
		cur_x = e->cursor->xview;
	line->str = ft_strinsert(line->str, to_cat, cur_x);
	++line->len;
	++e->cursor->x;
}

void	delete(t_editor *e)
{
	t_line	*line;
	int		cur_x;

	line = get_line(e, e->cursor->y);
	if (e->cursor->xview == 0)
	{
		del_line(line, e);
		return ;
	}
	cur_x = e->cursor->x;
	if (e->cursor->xview > e->cursor->x)
		cur_x = e->cursor->xview;	
	ft_memmove(&line->str[cur_x - 1], \
				&line->str[cur_x], \
				ft_strlen(&line->str[cur_x]) + 1);
	e->cursor->x = cur_x - 1;
	--line->len;
}

static void	insert_line(t_line *line, t_editor *e)
{
	t_line *n_line;
	int		cur_x;

	cur_x = e->cursor->x;
	if (e->cursor->x > e->cursor->xview)
		cur_x = e->cursor->xview;
	n_line = new_line(&line->str[cur_x]);
	if (!n_line)
		quit_free_msg("Alloc", 1, e);
	line->str[e->cursor->x] = '\r';
	line->str[e->cursor->x + 1] = 0;
	line->len = ft_strlen(line->str);
	n_line->next = line->next;
	n_line->prev = line;
	line->next = n_line;
	if (n_line->next)
		n_line->next->prev = n_line;
	e->cursor->x = 0;
	++e->cursor->y;
	++e->buf->nbr_line;
}

static void	del_line(t_line *line, t_editor *e)
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
	--e->buf->nbr_line;
	--e->cursor->y;
}
