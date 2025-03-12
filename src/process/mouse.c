#include "../../editor.h"

static void	press(t_cursor *pp, t_cursor *ip);
static void	release(t_editor *e, t_cursor *pp, t_cursor *ip);
static void	set_cursor(t_cursor *ip, char *i, t_editor *e);

void	mouse(t_editor *e, char input[2])
{
	static t_cursor	press_pos;
	t_cursor		*input_pos;

	input_pos = malloc(sizeof(t_cursor));
	if (!input_pos)
		quit_free_msg("Alloc", 1, e);
	set_cursor(input_pos, input + 1, e);
	if (input[0] == 35)
		release(e, &press_pos, input_pos);
	else if (input[0] < 35)
		press(&press_pos, input_pos);
	else if (input[0] == 64)
		highlight(e, &press_pos, input_pos);
	// ajouter input[0] 97 pour scrolldown et 96 up
	free(input_pos);
}

static void	press(t_cursor *pp, t_cursor *ip)
{
	// start highlighing
	pp->xview = ip->xview;
	pp->yview = ip->yview;
	pp->x = ip->x;
	pp->y= ip->y;
}

static void	release(t_editor *e, t_cursor *pp, t_cursor *ip)
{
	if (!is_same_pos(pp, ip))
	{
		printf_fd(2, "[%d][%d] to [%d][%d]\n", pp->xview, pp->yview, ip->xview, ip->yview);
		// stop highlighting
	}
	e->cursor->x = ip->x;
	e->cursor->y = ip->y;
	e->cursor->xview = ip->xview;
	e->cursor->yview = ip->yview;
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
	ip->y = ip->yview + e->win->starting_row - 1;
	line = get_line(e, ip->y);
	if (ip->xview <= 0)
	{
		ip->xview = get_xview_from_x(line, line->len, \
					e->tabstop, e->win->start_col) + 1;
	}
	ip->x = get_x_from_xview(line, ip->xview, \
				e->tabstop, e->win->start_col) - 1;
}
