#include "../editor.h"

static void	init_alloc(t_editor *data);
static void	init_window(t_window *win);
static void	init_cursor(t_cursor *cursor);
static void	init_buffer(t_buffer *buffer);

void	init_editor(t_editor *data, char *file_name)
{
	data->buf = NULL;
	data->tab_stop = 12;
	data->dirty = 0;
	data->f_name = file_name;
	data->mode = 0;
	data->win = NULL;
	data->cursor = NULL;
	data->clip_board = NULL;
	data->cmd = NULL;
	data->stat = NULL;
	init_alloc(data);
	init_buffer(data->buf);
	init_window(data->win);
	init_cursor(data->cursor);
	data->stat = ft_memset(data->stat, 32, data->win->width);
	enable_raw_mode(&data->o_ter);
}

static void	init_alloc(t_editor *data)
{
	data->buf = malloc(sizeof(t_buffer));
	if (!data->buf)
		quit_free_msg("Alloc", 1, data);
	data->win = malloc(sizeof(t_window));
	if (!data->win)
		quit_free_msg("Alloc", 1, data);
	data->cursor = malloc(sizeof(t_cursor));
	if (!data->cursor)
		quit_free_msg("Alloc", 1, data);
	data->stat = ft_calloc(sizeof(char), 1024);
	if (!data->stat)
		quit_free_msg("Alloc", 1, data);
	data->cmd = ft_calloc(sizeof(char), 1024);
	if (!data->cmd)
		quit_free_msg("Alloc", 1, data);
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
	win->starting_col = 0;
	win->starting_row = 0;
}

static void	init_cursor(t_cursor *cursor)
{
	cursor->x = 0;
	cursor->y = 0;
	cursor->xview = 0;
	cursor->yview = 0;
}

static void	init_buffer(t_buffer *buffer)
{
	buffer->nbr_line = 0;
	buffer->head = NULL;
}
