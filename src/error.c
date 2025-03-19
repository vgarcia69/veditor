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

static void	free_sel(t_selection *sel)
{
	if (sel)
	{
		if (sel->end)
			free(sel->end);
		if (sel->start)
			free(sel->start);
		free(sel);
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
	if (e->cpy)
	{
		if (e->cpy->head)
			free_line(e->cpy->head);
		free(e->cpy);
	}
	if (e->opt)
		free(e->opt);
	free_sel(e->sel);
	disable_raw_mode(&e->o_ter);
	quit_error_msg(str, code);
}
