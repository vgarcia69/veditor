#include "../../editor.h"

void	paste_single(t_line *line, int x, t_editor *e)
{
	char	*str;

	str = e->cpy->head->str;
	if (!check_capacity(line, str))
		realloc_line(e, line);
	line->str = ft_strinsert(line->str, str, x);
	line->len = ft_strlen(line->str);
	e->act = T_SINGLE;
}

char	*paste_first(t_line *line, int x, t_editor *e)
{
	t_line	*cpy;
	char	*carry;

	cpy = e->cpy->head;
	while (!check_capacity(line, cpy->str))
		realloc_line(e, line);
	carry = ft_strdup(&line->str[x]);
	if (!carry)
		quit_free_msg("Alloc", 1, e);
	ft_strncpy(&line->str[x], cpy->str, cpy->len + 1);
	line->len = ft_strlen(line->str);
	return (carry);
}

t_line	*paste_mid(t_line *line, t_editor *e, char *carry)
{
	t_line	*cpy;
	t_line	*paste;

	cpy = e->cpy->head;
	while (cpy->next)
	{
		cpy = cpy->next;
		paste = new_line(cpy->str);
		if (!paste)
		{
			free(carry);
			quit_free_msg("Alloc", 1, e);
		}
		insert_line(&line, paste);	
		line = paste;
		++e->cursor->y;
		++e->nb_line;
	}
	return (paste);
}

void	paste_last(t_line *last, t_editor *e, char *carry)
{
	t_line	*line;

	if (last->str[last->len - 1] == '\n')
	{
		line = new_line(carry);
		if (!line)
		{
			free(carry);
			quit_free_msg("Alloc", 1, e);
		}
		insert_line(&last, line);
		e->cursor->x = last->len;
	}
	else
	{
		while (!check_capacity(last, carry))
			realloc_line(e, last);
		ft_strcat(last->str, carry);
		e->cursor->x = last->len;
		last->len += ft_strlen(carry);
	}
	e->act = T_MULTI;
}

void	paste_single_node(t_line *line, t_editor *e)
{
	t_line	*cpy;

	cpy = new_line(e->cpy->head->str);
	if (!cpy)
		quit_free_msg("Alloc", 1, e);
	insert_line(&line, cpy);
	++e->nb_line;
	++e->cursor->y;
	e->act = T_SINGLE;
}
