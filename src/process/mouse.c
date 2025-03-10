
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
}

static void	press(t_cursor *pp, t_cursor *ip)
{
	// cancel highlight pour cpy
	pp->xview = ip->xview;
	pp->yview = ip->yview;
	pp->x = ip->x;
	pp->y= ip->y;
}

static void	release(t_editor *e, t_cursor *pp, t_cursor *ip)
{
	if (!is_same_pos(pp, ip))
	{
		printf_fd(2, "[%d][%d] et [%d][%d]\n", pp->xview, pp->yview, ip->xview, ip->yview);
		// copy_clip_board(e);
	}
	free(e->cursor);
	e->cursor = ip;
}

void	highlight(t_editor *e, t_cursor *pp, t_cursor *ip)
{
	
}

static void	set_cursor(t_cursor *ip, char *i, t_editor *e)
{
	t_line	*line;
	int		offset;

	offset = 32;
	ip->xview = i[0] - offset;
	ip->yview = i[1] - offset;
	ip->y = ip->yview + e->win->starting_row - 1;
	line = get_line(e, ip->y);
	ip->x = get_x_from_xview(line, ip->xview, e->tab_stop, e->win->starting_row) - 1;
}
