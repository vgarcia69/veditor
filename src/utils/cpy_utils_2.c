#include "../../editor.h"

void	cpy_node(t_line *line, t_editor *e)
{
	t_line	*cpy;

	cpy = new_line(line->str);
	if (!cpy)
		quit_free_msg("Alloc", 1, e);
	e->cpy->head = cpy;
	e->cpy->nb_line = 1;
}

void	paste_single_node(t_line *line, t_editor *e)
{
	t_line	*cpy;

	cpy = new_line(e->cpy->head->str);
	if (!cpy)
		quit_free_msg("Alloc", 1, e);
	insert_line(&line, cpy);
	++e->nb_line;
	++e->cursor->y;
}
