#include "../../../editor.h"

void	save(t_editor *e)
{
}

void	copy(t_editor *e)
{
	t_line *line = e->buf->head;

	while (line)
	{
		printf_fd(3, "[%s]", line->str);
		line = line->next;
	}
	quit_free_msg("byebye_t_editor *e", 1, e);
}

void	paste(t_editor *e)
{

}

void	undo(t_editor *e)
{

}

void	redo(t_editor *e)
{

}
