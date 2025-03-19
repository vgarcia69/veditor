#include "../../editor.h"

void	editor_refresh_win(t_editor *e)
{
	static time_t	last_time;
	time_t			elapsed_time;
	int				i;

	elapsed_time = get_time_ms();
	i = 0;
	if (elapsed_time - last_time > 20)
	{
		printf_fd(STDOUT_FILENO, "\033[?25l");
		if (e->act == T_MULTI || e->act == T_SINGLE)
		{
			while (i <= e->win->height)
			{
				printf_fd(STDOUT_FILENO, "\033[%dH\033[2K", i);
				++i;
			}
		}
		draw_window(e);
		if (e->act == OTHER || !last_time)
			draw_bottom(e->win->height, e->stat, e->mode, e->cmd);
		draw_cursor(e->cursor);
		draw_selection(e->sel, e);
		printf_fd(STDOUT_FILENO, "\033[?25h");
		last_time = elapsed_time;
	}
}
