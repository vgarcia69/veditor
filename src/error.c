#include "../editor.h"

void	quit_error_msg(char *str, int code)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit(code);
}

void	quit_free_msg(char *str, int code, t_editor *e)
{
	if (e->f_name)
		free(e->f_name);
	if (e->buf)
	{
		if (e->buf->head)
			free_line(e->buf->head);
		free(e->buf);
	}
	if (e->cursor)
		free(e->cursor);
	if (e->win)
		free(e->win);
	if (e->cmd)
		free(e->cmd);
	if (e->stat)
		free(e->stat);
	disable_raw_mode(&e->o_ter);
	quit_error_msg(str, code);
}

void	print_err(char *str)
{
	printf_fd(STDERR_FILENO, str);
}
