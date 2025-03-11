#include "../../editor.h"

static void	height_arrows(char c, t_editor *e);
static void	width_arrows(char c, t_editor *e);

void	arrow(t_editor *e, char c)
{
	if (c == 'A' || c == 'B')
		height_arrows(c, e);
	if (c == 'C' || c == 'D')
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
	if (c == 'C' && line->str[cursor->x + 1])
		++cursor->x;
	else if (c == 'D' && cursor->x > 0)
		--cursor->x;
}

static void	height_arrows(char c, t_editor *e)
{
	if (c == 'A' && e->cursor->y > 0)
		--e->cursor->y;
	else if (c == 'B' && e->cursor->y < e->buf->nbr_line - 1)
		++e->cursor->y;
}
