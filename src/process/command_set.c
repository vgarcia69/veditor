#include "../../editor.h"

char	*tablen_cmd(t_editor *e, char *arg)
{
	int	request;

	request = ft_atoi(arg);
	if (request >= 2 && request <= 24)
	{
		e->win->tabstop = request;
		return ("Tab length updated !");
	}
	return (WRONG_NUM);
}

char	*mouse_cmd(t_editor *e, char *arg) 
{

	return (WRONG_NUM);
}

char	*lenstr_cmd(t_editor *e, char *arg)
{

	return (WRONG_NUM);
}

char	*color_cmd(t_editor *e, char *arg) 
{

	return (WRONG_NUM);
}

