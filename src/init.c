#include "../editor.h"

static void	init_alloc(t_editor *e);
static void	init_window(t_window *win);
static void	init_clipboard_cursor(t_clipboard *cpy, t_cursor *cursor);
static void init_option(t_option *opt);

void	init_editor(t_editor *e, char *file_name)
{
	e->dirty = 0;
	e->f_name = file_name;
	e->mode = 0;
	e->win = NULL;
	e->cursor = NULL;
	e->cpy = NULL;
	e->cmd = NULL;
	e->stat = NULL;
	e->sel = NULL;
	e->nb_line = 0;
	e->head = NULL;
	init_alloc(e);
	init_option(e->opt);
	init_clipboard_cursor(e->cpy, e->cursor);
	init_window(e->win);
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
	e->cpy = malloc(sizeof(t_clipboard));
	if (!e->cpy)
		quit_free_msg("Alloc", 1, e);
	e->opt = malloc(sizeof(t_clipboard));
	if (!e->opt)
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
	win->tabstop = 8;
	win->margin_left = 0;
}

static void	init_clipboard_cursor(t_clipboard *cpy, t_cursor *cursor)
{
	cpy->head = NULL;
	cpy->nb_line = 0;
	cpy->type = 0;
	cursor->x = 0;
	cursor->y = 0;
	cursor->xview = 0;
	cursor->yview = 0;
}

static void init_option(t_option *opt)
{
	opt->is_len = 1;
	opt->is_mouse_active = 1;
	opt->tablen = 8;
	opt->is_color_active = 1;
}
