#include "../../../editor.h"

void	go_begin_line(t_editor *e)
{
	e->cursor->x = 0;
}

void	go_end_line(t_editor *e)
{
	t_line *line;

	line = get_line(e, e->cursor->y);
	e->cursor->x = line->len - 1;
}

void	select_line(t_editor *e)
{

}

void	select_word(t_editor *e)
{

}

void	delete_line(t_editor *e)
{

}
