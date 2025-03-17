#include "../editor.h"

static void	init_alloc(t_editor *e);
static void	init_window(t_window *win);
static void	init_cursor(t_cursor *cursor);

void	init_editor(t_editor *e, char *file_name)
{
	e->dirty = 0;
	e->f_name = file_name;
	e->mode = 0;
	e->win = NULL;
	e->cursor = NULL;
	e->clip_board = NULL;
	e->cmd = NULL;
	e->stat = NULL;
	e->sel = NULL;
	e->nb_line = 0;
	e->head = NULL;
	init_alloc(e);
	e->sel->end = NULL;
	e->sel->start = NULL;
	init_window(e->win);
	init_statbar(e);
	init_cursor(e->cursor);
	init_selection(e);
	init_fds(e);
	enable_raw_mode(&e->o_ter);
}

static void	init_alloc(t_editor *e)
{
	e->win = malloc(sizeof(t_window));
	if (!e->win)
		quit_free_msg("Alloc", 1, e);
	e->cursor = malloc(sizeof(t_cursor));
	if (!e->cursor)
		quit_free_msg("Alloc", 1, e);
	e->stat = ft_calloc(sizeof(char), 1024);
	if (!e->stat)
		quit_free_msg("Alloc", 1, e);
	e->cmd = ft_calloc(sizeof(char), 1024);
	if (!e->cmd)
		quit_free_msg("Alloc", 1, e);
	e->sel = malloc(sizeof(t_selection));
	if (!e->sel)
		quit_free_msg("Alloc", 1, e);
}

static void	init_window(t_window *win)
{
	struct winsize ws;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
	{
		ws.ws_col = 96;
		ws.ws_row = 24;
	}
	win->height = ws.ws_row - 2;
	win->width = ws.ws_col;
	win->start_col = 0;
	win->start_row = 0;
	win->tabstop = 8; //  changer ptet
	win->margin_left = -1;
}

static void	init_cursor(t_cursor *cursor)
{
	cursor->x = 0;
	cursor->y = 0;
	cursor->xview = 0;
	cursor->yview = 0;
}
