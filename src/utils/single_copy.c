#include "../../editor.h"

void	cpy_node(t_line *line, t_editor *e)
{
	t_line	*cpy;

	cpy = new_line(line->str);
	if (!cpy)
		quit_free_msg("Alloc", 1, e);
	e->cpy->head = cpy;
	e->cpy->nb_line = 1;
}

void	cpy_single(int start, int end, int y, t_editor *e)
{
	t_line	*line;	
	char	*str;
	int		str_len;

	str_len = end - start;
	line = get_line(e, y);
	str = ft_calloc(sizeof(char), str_len + 1);
	if (!str)
		quit_free_msg("Alloc", 1, e);
	ft_strncpy(str, &line->str[start], str_len);
	line = new_line(str);
	free(str);
	if (!line)
		quit_free_msg("Alloc", 1, e);
	e->cpy->head = line;
	e->cpy->nb_line = 1;
}
