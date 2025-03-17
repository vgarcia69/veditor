#include "../../editor.h"

void	paste_single(t_line *line, int x, t_editor *e)
{
	char	*str;

	str = e->cpy->head->str;
	if (!check_capacity(line, str))
		realloc_line(e, line);
	line->str = ft_strinsert(line->str, str, x);
}

void	paste_multi(t_line *line, int x, t_editor *e)
{

}
