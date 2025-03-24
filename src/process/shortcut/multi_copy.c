#include "../../../editor.h"


void	cpy_first(t_cursor *start, t_editor *e)
{
	t_line	*line;	
	char	*str;

	line = get_line(e, start->y);
	str = ft_calloc(sizeof(char), line->len - start->x + 1);
	if (!str)
		quit_free_msg("Alloc", 1, e);
	ft_strcpy(str, &line->str[start->x]);
	line = new_line(str);
	free(str);
	if (!line)
		quit_free_msg("Alloc", 1, e);
	e->cpy->head = line;
	e->cpy->nb_line = 1;
}

void	cpy_mid(t_cursor *start, t_cursor *end, t_editor *e)
{
	t_line	*line;
	t_line	*n_line;
	int		i;

	i = start->y + 1;
	while (i < end->y)
	{
		line = get_line(e, i);
		n_line = new_line(line->str);
		if (!n_line)
			quit_free_msg("Alloc", 1, e);
		addback_line(&e->cpy->head, n_line);
		++e->cpy->nb_line;
		++i;
    }
}

void	cpy_last(t_cursor *end, t_editor *e)
{
	t_line	*line;
	t_line	*last;
	char	*str;

	line = get_line(e, end->y);
	str = ft_calloc(sizeof(char), end->x + 1);
	if (!str)
		quit_free_msg("Alloc", 1, e);
	ft_strncpy(str, line->str, end->x);
	last = new_line(str);
	free(str);
	if (!last)
		quit_free_msg("Alloc", 1, e);
	addback_line(&e->cpy->head, last);
	++e->cpy->nb_line;
}

void	clear_cpy(t_clipboard *cpy)
{
	if (cpy->head)
		free_line(cpy->head);
	cpy->nb_line = 0;
	cpy->type = 0;
}
