#include "../../editor.h"

void	editor_refresh_win(t_editor *e)
{
	printf_fd(STDOUT_FILENO, "\033[2J");
	printf_fd(STDOUT_FILENO, "\033[?25l");
	draw_window(e);
	draw_bottom(e->win->height, e->stat, e->mode, e->cmd);
	draw_cursor(e->cursor);
	draw_selection(e->sel, e);
	printf_fd(STDOUT_FILENO, "\033[?25h");
}
