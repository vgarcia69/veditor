#include "../../editor.h"

void	draw_window(t_editor *e)
{
	int		j;

	e->buf->line = e->buf->head;
	j = 0;
	while (e->buf->line->next && e->win->starting_row)
		e->buf->line = e->buf->line->next;
	while (e->buf->line->next && j < e->win->height)
	{
	  	printf_fd(STDOUT_FILENO, "\033[%d;1H", j++);
		draw_line(e);
		e->buf->line = e->buf->line->next;
	}
	e->buf->line = e->buf->head;
}

void	draw_cursor(t_cursor *c)
{
	printf_fd(STDOUT_FILENO, "\033[%d;%dH", c->yview + 1, c->xview + 1);
	printf_fd(STDOUT_FILENO, "\033[7m");
	printf_fd(STDOUT_FILENO, "\033[%d;%dH", c->yview + 1, c->xview + 1);
	printf_fd(STDOUT_FILENO, "\033[0m");
}

void	draw_status(int height, char *stat, int mode)
{
	printf_fd(STDOUT_FILENO, "\033[%d;1H\033[7m", height + 1);
	printf_fd(STDOUT_FILENO, "%s", stat);
	printf_fd(STDOUT_FILENO, "\033[%d;1H\033[0m", height + 2);
}

void	draw_command(int height, char *cmd)
{
	printf_fd(STDOUT_FILENO, "\033[%d;1H", height + 2);
	printf_fd(STDOUT_FILENO, "%s", cmd);
}
