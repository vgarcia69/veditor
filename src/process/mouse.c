#include "../../editor.h"

static void	set_cursor(t_cursor *ip, char *i, t_editor *e);

void	mouse(t_editor *e, char input[3])
{
	t_cursor		*input_pos;

	input_pos = malloc(sizeof(t_cursor));
	if (!input_pos)
		quit_free_msg("Alloc", 1, e);
	set_cursor(input_pos, input + 1, e);
	if (input[0] == 35)
	{
		cp_cursor(e->cursor, input_pos);
		cp_cursor(e->sel->end, input_pos);
	}
	else if (input[0] < 35)
	{
		if (e->sel->is_active)
			e->sel->is_active = 0;
		else
			e->sel->is_active = 1;
		cp_cursor(e->sel->start, input_pos);
	}
	free(input_pos);
}

static void	set_cursor(t_cursor *ip, char *i, t_editor *e)
{
	t_line	*line;
	int		offset;

	offset = 32;
	ip->xview = i[0] - offset;
	ip->yview = i[1] - offset;
	if (ip->yview >= e->buf->nbr_line || ip->yview <= 0)
		ip->yview = e->buf->nbr_line;
	ip->y = ip->yview + e->win->start_row - 1;
	line = get_line(e, ip->y);
	if (ip->xview <= 0)
	{
		ip->xview = get_xview_from_x(line, line->len, \
					e->tabstop, e->win->start_col) + 1;
	}
	ip->x = get_x_from_xview(line, ip->xview, \
				e->tabstop, e->win->start_col) - 1;
}
