#include "../../editor.h"

/*
met a jour l affichage window, status, command
*/

void	editor_refresh_win(t_editor *e)
{
	// check_scroll();
	printf_fd(STDOUT_FILENO, "\033[2J");
	printf_fd(STDOUT_FILENO, "\033[?25l");
	draw_window(e);
	draw_status(e->win->height, e->stat, e->mode);
	draw_command(e->win->height, e->cmd);
	draw_cursor(e->cursor);
	printf_fd(STDOUT_FILENO, "\033[?25h");
}

//scroll / cursor
