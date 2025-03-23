#include "../../editor.h"

static void	set_cursor(t_cursor *ip, unsigned char *i, t_editor *e);

void	mouse(t_editor *e, unsigned char input[3])
{
	t_cursor		*input_pos;

	input_pos = malloc(sizeof(t_cursor));
	if (!input_pos)
		quit_free_msg("Alloc", 1, e);
	if (input[0] == 32)
	{
		e->sel->is_active = 0;
		set_cursor(input_pos, input + 1, e);
		cp_cursor(e->sel->start, input_pos);
		cp_cursor(e->sel->end, input_pos);
		printf_fd(3, "mouse click view x[%d]xv[%d]y[%d]yv[%d]\n", input_pos->x, input_pos->xview, input_pos->y, input_pos->yview);
	}
	else if (input[0] == 64)
	{
		set_cursor(input_pos, input + 1, e);
		if (is_ordered(e->sel->start, input_pos))
			cp_cursor(e->sel->end, input_pos);
		else
			cp_cursor(e->sel->start, input_pos);
		if (!is_same_pos(e->sel->start, e->sel->end))
			e->sel->is_active = 1;
	}
	free(input_pos);
}

static void	set_cursor(t_cursor *ip, unsigned char *i, t_editor *e)
{
	t_line		*line;
	t_window	*view;
	int			offset;
	int			max_y;
	int			max_x;

	offset = 32;
	view = e->win;
	max_y = ft_min(e->nb_line - view->start_row, view->height);
	ip->yview = ft_min(i[1] - offset, max_y);
	ip->y = ip->yview + view->start_row - 1;
	line = get_line(e, ip->y);
	max_x = get_xview_from_x(line, line->len, view);
	ip->xview = ft_min(i[0] - offset, max_x);
	ip->x = get_x_from_xview(line, ip->xview, view);
	if (line->str[ip->x] == '\t')
		ip->xview -= get_tabwidth(ip->xview, view->tabstop);
	cp_cursor(e->cursor, ip);
}
