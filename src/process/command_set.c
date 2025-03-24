#include "../../editor.h"

char	*tabstop_cmd(t_editor *e, char *arg)
{
	int	request;

	request = ft_atoi(arg);
	if (request >= 2 && request <= 24)
	{
		e->win->tabstop = request;
		update_win(e);
		return ("Tab length updated !");
	}
	return (WRONG_NUM);
}

char	*mouse_cmd(char *arg) 
{
	int	request;
	char	*comment;

	request = ft_atoi(arg);
	if (request == 0)
	{
		printf_fd(STDOUT_FILENO, "\033[?1002l");
		comment = "Mouse Disabled";
	}
	else if (request == 1)
	{
		printf_fd(STDOUT_FILENO, "\033[?1002h");
		comment = "Mouse Enabled";
	}
	else
		comment = NOT_FOUND;
	return (comment);
}

char	*lenstr_cmd(t_editor *e, char *arg)
{
	int		request;
	char	*comment;

	request = ft_atoi(arg);
	if (request == 0)
	{
		e->len_visu = 0;
		e->win->margin_left = get_margin(e);
		comment = "String Length Visualizer Disabled";
	}
	else if (request == 1)
	{
		e->len_visu = 1;
		e->win->margin_left = get_margin(e);
		comment = "String Length Visualizer Enabled";
	}
	else
		comment = NOT_FOUND;
	return (comment);
}

char	*name_cmd(t_editor *e, char *arg, char **secure)
{
	char	*comment;
	int		fd;

	if (e->f_name)
		return ("Error : File has already a name");
	fd = open(arg, O_EXCL | O_CREAT, 0755);
	if (fd == -1)
		comment = "Error : File Already exist";
	else
	{
		close(fd);
		e->f_name = ft_strdup(arg);
		if (e->f_name == NULL)
		{
			free_tab(secure);
			quit_free_msg("Alloc", 1, e);
		}
		comment = "File successfully created";
	}
	return (comment);
}
