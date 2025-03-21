#include "../../editor.h"

static void	init_alloc(t_editor *e);
static void	init_vars(t_editor *e, char *file_name);

void	init_editor(t_editor *e, char *file_name)
{
	init_vars(e, file_name);
	init_alloc(e);
	init_struct_1(e->cpy, e->cursor, e->win);
	init_struct_2(e);
	init_struct_3(e);
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
	e->stat = ft_calloc(sizeof(char), 256);
	if (!e->stat)
		quit_free_msg("Alloc", 1, e);
	e->cmd = ft_calloc(sizeof(char), 256);
	if (!e->cmd)
		quit_free_msg("Alloc", 1, e);
	e->sel = malloc(sizeof(t_selection));
	if (!e->sel)
		quit_free_msg("Alloc", 1, e);
	e->cpy = malloc(sizeof(t_clipboard));
	if (!e->cpy)
		quit_free_msg("Alloc", 1, e);
	e->buffer = malloc(sizeof(t_display));
	if (!e->buffer)
		quit_free_msg("Alloc", 1, e);
}

static void	init_vars(t_editor *e, char *file_name)
{
	e->f_name = file_name;
	e->dirty = 0;
	e->mode = 0;
	e->len_visu = 0;
	e->nb_line = 0;
	e->win = NULL;
	e->cursor = NULL;
	e->cpy = NULL;
	e->cmd = NULL;
	e->stat = NULL;
	e->sel = NULL;
	e->head = NULL;
	e->buffer = NULL;
}

int	open_file(char *file, t_editor *e)
{
	int	fd;

	if (!file)	
		return (0);
	fd = open(file, O_RDONLY, 0777);
	if (fd == -1 && errno == 13)
		quit_free_msg("Permission Denied", 1, e);
	return (fd);
}
