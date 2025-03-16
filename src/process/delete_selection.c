#include "../../editor.h"

static char	*join_strings(t_line *start, t_line *end, t_selection *sel);
static void	update_list(t_line *start, t_line *end, \
				t_line *new, t_editor *e);

void	delete_selection(t_selection *sel, t_editor *e)
{
	t_line	*new;
	t_line	*start;
	t_line	*end;
	char	*temp;

	sel->is_active = 0;
	if (!is_ordered(sel->start, sel->end))
		ft_revptr((void **)&sel->start, (void **)&sel->end);
	start = get_line(e, sel->start->y);
	end = get_line(e, sel->end->y);
	temp = join_strings(start, end, sel);
	if (!temp)
		quit_free_msg("Alloc", 1, e);
	new = new_line(temp);
	if (!new)
	{
		free(temp);
		quit_free_msg("Alloc", 1, e);
	}
	free(temp);
	new->str[new->len] = '\n';
	new->str[++new->len] = '\0';
	update_list(start, end, new, e);
	e->cursor->x = sel->start->x;
	e->cursor->y = sel->start->y;
}

static char	*join_strings(t_line *start, t_line *end, t_selection *sel)
{
	int		new_len;
	char	*new_string;

	new_len = start->len + ft_strlen(&end->str[sel->end->x + 1]) + 1;
	new_string = ft_calloc(sizeof(char), (new_len + 2));
	if (!new_string)
		return (NULL);
	new_string = ft_strncpy(new_string, start->str, sel->start->x);
	new_string = ft_strcpy(new_string, &end->str[sel->end->x + 1]);
	new_string[new_len] = '\n';
	new_string[new_len + 1] = '\0';
	return (new_string);
}

static void	update_list(t_line *start, t_line *end, \
				t_line *new, t_editor *e)
{
	t_line	*temp;

	if (start->prev)
	{
		start->prev->next = new;
		new->prev = start->prev;
	}
	else
		e->head = new;
	if (end->next)
	{
		new->next = end->next;
		end->next->prev = new;
	}
	e->nb_line -= e->sel->end->y - e->sel->start->y;
	while (start != end)
	{
		temp = start;
		start = start->next;
		free(temp->str);
		free(temp);
	}
	free(start->str);
	free(start);
}
