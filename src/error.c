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
	if (e->sel)
	{
		if (e->sel->end)
			free(e->sel->end);
		if (e->sel->start)
			free(e->sel->start);
		free(e->sel);
	}
	disable_raw_mode(&e->o_ter);
	quit_error_msg(str, code);
}
