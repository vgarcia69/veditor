#include "../../editor.h"

static void	insert_newline(t_line *line, t_editor *e);

void	insert(t_editor *e, char c)
{
	t_line	*line;
	char	to_cat[2];
	int		cur_x;

	e->dirty = 1;
	line = get_line(e, e->cursor->y);
	if (c == '\r' || c == '\n')
	{
		insert_newline(line, e);
		return ;
	}
	to_cat[0] = c;
	to_cat[1] = '\0';
	while (!check_capacity(line, to_cat))
		realloc_line(e, line);
	cur_x = get_x_from_xview(line, e->cursor->xview, e->win);
	line->str = ft_strinsert(line->str, to_cat, cur_x);
	++line->len;
	++e->cursor->x;
}

static void	insert_newline(t_line *line, t_editor *e)
{
	t_line	*n_line;
	int		cur_x;

	cur_x = get_x_from_xview(line, e->cursor->xview, e->win);
	n_line = new_line(&line->str[cur_x]);
	if (!n_line)
		quit_free_msg("Alloc", 1, e);
	line->str[cur_x] = '\n';
	line->str[cur_x + 1] = 0;
	line->len = ft_strlen(line->str);
	insert_line(&line, n_line);
	e->cursor->x = 0;
	++e->cursor->y;
	++e->nb_line;
}
