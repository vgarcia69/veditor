#include "../../editor.h"

void	draw_window(t_editor *e)
{
	t_line	*line;
	int		i;

	i = 0;
	line = get_line(e, e->win->start_row);
	while (line && i < e->win->height)
	{
	  	printf_fd(STDOUT_FILENO, "\033[%d;1H", ++i);
		draw_line(e, line);
	  	// printf_fd(STDOUT_FILENO, "\033[%d;%dH[%d]", i, e->win->width - 5, line->len - 1); a mettre en option
		line = line->next;
	}
	while (i < e->win->height)
	{
	  	printf_fd(STDOUT_FILENO, "\033[%d;1H", ++i);
		printf_fd(STDOUT_FILENO, "~");
	}
}

void	draw_cursor(t_cursor *c)
{
	printf_fd(STDOUT_FILENO, "\033[%d;%dH", c->yview + 1, c->xview + 1);
	printf_fd(STDOUT_FILENO, "\033[7m");
	printf_fd(STDOUT_FILENO, "\033[%d;%dH", c->yview + 1, c->xview + 1);
	printf_fd(STDOUT_FILENO, "\033[0m");
}

void	draw_bottom(int height, char *stat, int mode, char *cmd)
{
	printf_fd(STDOUT_FILENO, "\033[%d;1H\033[1;7m", height + 1);
	printf_fd(STDOUT_FILENO, "%s", stat);
	printf_fd(STDOUT_FILENO, "\033[%d;1H\033[0m", height + 2);
	printf_fd(STDOUT_FILENO, "\033[%d;1H", height + 3);
	printf_fd(STDOUT_FILENO, "%s", cmd);
}
