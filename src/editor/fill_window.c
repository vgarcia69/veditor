#include "../../editor.h"

static void	fill_index(t_window *view, int index, t_display *buf, t_editor *e);
static void	fill_strlen(int nbr, t_display *buf, t_editor *e);
static void	fill_text(int y, char *str, t_display *buf, t_editor *e);

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
		fill_index(view, index + 1, buffer, e);
		if (e->len_visu)
			fill_strlen(row->len - 1, buffer, e);
		fill_text(index + view->start_row, row->str, buffer, e);
		++index;
		row = row->next;
		append_string(buffer, e, "\033[%d;1H", index + 1);
	}
	while (index < view->height)
		append_string(buffer, e, BLUE"\033[%d;1H~"RESET, ++index);
}

static void	fill_index(t_window *view, int index, t_display *buf, t_editor *e)
{
	int	x_index;
	int	nb_index;
	int	max_index;

	nb_index = index + view->start_row;
	max_index = view->start_row + view->height;
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

	on_off = 0;
	view_x = 0;
	x = ft_min(e->win->start_col, ft_strlen(str));
	while (str[x] && view_x + e->win->margin_left < e->win->width)
	{
		update_hl(&on_off, (int[]){x, y}, buf, e);
		if (str[x] == '\t')
		{
			tab = get_tabwidth(view_x, e->win->tabstop);
			while (tab-- && ++view_x-1 < e->win->width)
				append_string(buf, e, " ");
		}
		else
		{
			append_string(buf, e, "%c", str[x]);
			++view_x;
		}
		++x;
	}
	append_string(buf, e, RESET);
}
