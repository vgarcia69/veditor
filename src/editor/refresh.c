#include "../../editor.h"

void	editor_refresh_win(t_editor *e)
{
	static time_t	last_time;
	time_t			elapsed_time;
	char			*buffer;

	elapsed_time = get_time_ms();
	if (elapsed_time - last_time > 40)
	{
		buffer = ft_calloc(1, (e->win->width) * (e->win->height) * 4);
		if (!buffer)
			quit_free_msg("Alloc", 1, e);
		buffer = clear_window(e, buffer);
		buffer = add_buffer_window(e, buffer);
		if (e->sel->is_active)
			buffer = add_buffer_selection(e->sel, e, buffer);
		ft_putstr_fd(buffer, STDOUT_FILENO);
		free(buffer);
		draw_bottom(e->win->height, e->stat, e->cmd);
		if (!e->sel->is_active && e->mode == INSERT)
			draw_cursor(e->cursor);
		last_time = elapsed_time;
	}
}

void	draw_cursor(t_cursor *c)
{
	printf_fd(STDOUT_FILENO, "\033[%d;%dH", c->yview + 1, c->xview + 1);
	printf_fd(STDOUT_FILENO, "\033[7m");
	printf_fd(STDOUT_FILENO, "\033[%d;%dH", c->yview + 1, c->xview + 1);
	printf_fd(STDOUT_FILENO, "\033[0m");
}

void	draw_bottom(int height, char *stat, char *cmd)
{
	printf_fd(STDOUT_FILENO, "\033[%d;1H\033[1;7m", height + 1);
	printf_fd(STDOUT_FILENO, "%s", stat);
	printf_fd(STDOUT_FILENO, "\033[%d;1H\033[0m", height + 2);
	printf_fd(STDOUT_FILENO, "\033[%d;1H\033[2K", height + 3);
	printf_fd(STDOUT_FILENO, "%s", cmd);
}
