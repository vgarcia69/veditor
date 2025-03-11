
#include "../../editor.h"

static void	insert_line(t_line *line, t_editor *e);
static void	del_line(t_line *line, t_editor *e);

void	insert(t_editor *e, char c)
{
	t_line	*line;
	char	to_cat[2];

	printf_fd(2, "%d, %d | %d, %d\n", e->cursor->xview, e->cursor->yview, e->cursor->x, e->cursor->y);
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
	line->str = ft_strinsert(line->str, to_cat, e->cursor->x);
	++line->len;
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
	--line->len;
}

/*
gros bug d affichage ?
si tu suppr et entre fonctions a revoir
ou meme revoir yview ? dependant des efforts
*/
static void	insert_line(t_line *line, t_editor *e)
{
	t_line *n_line;

	n_line = new_line(&line->str[e->cursor->x]);
	if (!n_line)
		quit_free_msg("Alloc", 1, e);
	line->str[e->cursor->x] = '\r';
	line->str[e->cursor->x + 1] = 0;
	line->len = ft_strlen(line->str);
	n_line->next = line->next;
	n_line->prev = line;
	line->next = n_line;
	e->cursor->x = 0;
	++e->cursor->y;
	++e->buf->nbr_line;
	printf_fd(2,"n_line[%s]\nline[%s]\n", n_line->str, line->str);
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
	line->prev->len += line->len;
	e->cursor->x = line->prev->len;
	free(line->str);
	free(line);
	--e->buf->nbr_line;
	--e->cursor->y;
}
