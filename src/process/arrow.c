#include "../../editor.h"

static void	height_arrows(char c, t_editor *e);
static void	width_arrows(char c, t_editor *e);

void	arrow(t_editor *e, char c)
{
	printf_fd(3, "move x[%d]xv[%d]y[%d]yv[%d]\n", e->cursor->x, e->cursor->xview, e->cursor->y, e->cursor->yview);
	e->sel->is_active = 0;
	if (c == ARROW_UP || c == ARROW_DOWN)
		height_arrows(c, e);
	if (c == ARROW_RIGHT || c == ARROW_LEFT)
		width_arrows(c, e);
}

static void	width_arrows(char c, t_editor *e)
{
	t_cursor	*cursor;
	t_line		*line;

	cursor = e->cursor;
	line = get_line(e, cursor->y);
	if (cursor->x >= line->len)
		cursor->x = line->len - 1;
	if (c == ARROW_RIGHT && line->str[cursor->x + 1])
		++cursor->x;
	else if (c == ARROW_LEFT && cursor->x > 0)
		--cursor->x;
}

static void	height_arrows(char c, t_editor *e)
{
	if (c == ARROW_UP && e->cursor->y > 0)
		--e->cursor->y;
	else if (c == ARROW_DOWN && e->cursor->y < e->nb_line - 1)
		++e->cursor->y;
	if (e->win->start_col >= e->win->width)
		e->win->start_col = 0;
}
