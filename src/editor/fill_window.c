#include "../../editor.h"

static void	fill_index(t_window *view, int index, t_display *buf, t_editor *e);
static void	fill_strlen(int nbr, t_display *buf, t_editor *e);
static void	fill_text(int y, char *str, t_display *buf, t_editor *e);
static void	update_hl(int *on_off, int coords[2], t_display *buf, t_editor *e);

void	fill_window(t_display *buffer, t_editor *e)
{
	t_line		*row;
	t_window	*view;
	int			index;

	index = 0;
	view = e->win;
	row = get_line(e, view->start_row);
	append_string(buffer, e, "\033[1;1H\033[2J");	
	while (row && index < view->height)
	{
		fill_index(view, index, buffer, e);
		if (e->len_visu)
			fill_strlen(row->len - 1, buffer, e);
		fill_text(index + view->start_row, row->str, buffer, e);
		append_string(buffer, e, "\033[%d;1H", index + 1);
		row = row->next;
		++index;
	}
	while (index < view->height)
		append_string(buffer, e, BLUE"\033[%d;1H~"RESET, index++);
}

static void	fill_index(t_window *view, int index, t_display *buf, t_editor *e)
{
	int	x_index;
	int	nb_index;
	int	max_index;

	nb_index = index + view->start_row;
	max_index = index + view->start_row + view->height;
	x_index = len_int(max_index) - len_int(nb_index);
	while (x_index--)
		append_string(buf, e, " ");
	append_string(buf, e, YELLOW"%d "RESET, nb_index);
}

static void	fill_strlen(int nbr, t_display *buf, t_editor *e)
{
	int	max_nbr;
	int x_param;

	max_nbr = get_max_len(e->head) - 1;
	x_param = len_int(max_nbr) - len_int(nbr);
	while (x_param--)
		append_string(buf, e, " ");
	append_string(buf, e, "["BLUE"%d"RESET"] ", nbr);
}

static void	fill_text(int y, char *str, t_display *buf, t_editor *e)
{
	int			x;
	int			tab;
	int			on_off;
	int			view_x;
	t_window	*view;

	on_off = 0;
	view = e->win;
	view_x = view->margin_left + view->start_col;
	x = view->start_col;
	while (str[x] && view_x < view->width)
	{
		update_hl(&on_off, (int[]){x, y}, buf, e);
		if (str[x] == '\t')
		{
			tab = get_tabwidth(view_x, view->tabstop);
			while (tab-- && view_x++ < view->width)
				append_string(buf, e, " ");
		}
		else
		{
			append_string(buf, e, "%c", str[x]);
			++view_x;
		}
		++x;
	}
}

static void	update_hl(int *on_off, int coords[2], t_display *buf, t_editor *e)
{
	t_cursor	*start;
	t_cursor	*end;

	if (!e->sel->is_active)
		return ;
	start = e->sel->start;
	end = e->sel->end;
	if (coords[1] >= start->y && coords[1] <= end->y
		&& coords[0] >= start->x && coords[0] <= end->x)
	{
		if (*on_off == 0)
		{
			append_string(buf, e, INVERT);
			*on_off = 1;
		}
	}
	else if (*on_off == 1)
	{
		append_string(buf, e, RESET);	
		*on_off = 0;
	}
}
