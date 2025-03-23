#include "../../editor.h"

void	fill_cursor(t_display *buffer, t_editor *e)
{
	int	x;
	int y;

	if (e->sel->is_active)
		append_string(buffer, e, "\033[?25l");
	else if (e->mode == COMMAND)
		append_string(buffer, e, INVERT"\033[?25h"RESET);
	else
	{
		x = e->cursor->xview;
		y = e->cursor->yview;
		append_string(buffer, e, INVERT"\033[?25h\033[%d;%dH"RESET, y, x);
	}
}

void	fill_bottom(t_display *buffer, t_editor *e)
{
	int	stat_y;
	int	cmd_y;

	stat_y = e->win->height + 1;
	cmd_y = e->win->height + 2;
	append_string(buffer, e, INVERT BOLD"\033[%d;1H%s" RESET, stat_y, e->stat);
	append_string(buffer, e, "\033[%d;1H%s", cmd_y, e->cmd);
}
