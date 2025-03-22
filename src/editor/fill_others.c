#include "../../editor.h"

void	fill_cursor(t_display *buffer, t_editor *e)
{
	int	x;
	int y;

	x = e->cursor->xview + 1;
	y = e->cursor->yview + 1;
	append_string(buffer, e, INVERT"\033[%d;%dH"RESET, y, x);
	append_string(buffer, e, "\033[25l");
}

// void	fill_cursor(t_display *buffer, t_editor *e)
// {

// }
