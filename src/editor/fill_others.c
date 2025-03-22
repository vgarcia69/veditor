#include "../../editor.h"

void	fill_cursor(t_display *buffer, t_editor *e)
{
	int	x;
	int y;

	if (e->sel->is_active)
		append_string(buffer, e, "\033[?25l");
	else
	{
		x = e->cursor->xview + 1;
		y = e->cursor->yview + 1;
		append_string(buffer, e, INVERT"\033[?25h\033[%d;%dH"RESET, y, x);
	}
}

// void	fill_cursor(t_display *buffer, t_editor *e)
// {

// }
