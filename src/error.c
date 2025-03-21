#include "../editor.h"

void	quit_error_msg(char *str, int code)
{
	if (code)
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	exit(code);
}

static void	quit_free_2(t_editor *e)
{
	if (e->sel)
	{
		if (e->sel->end)
			free(e->sel->end);
		if (e->sel->start)
			free(e->sel->start);
		free(e->sel);
	}
	if (e->cpy)
	{
		if (e->cpy->head)
			free_line(e->cpy->head);
		free(e->cpy);
	}
	if (e->buffer)
	{
		if (e->buffer->content)
			free(e->buffer->content);
		free(e->buffer);
	}
}

void	quit_free_msg(char *str, int code, t_editor *e)
{
	if (e->f_name)
		free(e->f_name);
	if (e->head)
		free_line(e->head);
	if (e->cursor)
		free(e->cursor);
	if (e->win)
		free(e->win);
	if (e->cmd)
		free(e->cmd);
	if (e->stat)
		free(e->stat);
	quit_free_2(e);
	disable_raw_mode(&e->o_ter);
	quit_error_msg(str, code);
}
