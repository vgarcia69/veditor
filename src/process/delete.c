/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:46:14 by v                 #+#    #+#             */
/*   Updated: 2025/03/15 18:55:13 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../editor.h"

static void	delete_newline(t_line *line, t_editor *e);

void	delete(t_editor *e)
{
	t_line	*line;
	int		cur_x;

	line = get_line(e, e->cursor->y);
	if (e->sel->is_active)
	{
		delete_selection(e->sel, e);
		return ;
	}
	else if (e->cursor->xview == 0)
	{
		delete_newline(line, e);
		return ;
	}
	cur_x = get_x_from_xview(line, e->cursor->xview, e->win);
	ft_memmove(&line->str[cur_x - 1], \
				&line->str[cur_x], \
				ft_strlen(&line->str[cur_x]) + 1);
	--e->cursor->x;
	--line->len;
}

static void	delete_newline(t_line *line, t_editor *e)
{
	if (!line->prev)
		return ;
	line->prev->next = line->next;
	while (!check_capacity(line->prev, line->str))
		realloc_line(e, line->prev);
	ft_memcpy(&line->prev->str[line->prev->len - 1], \
				line->str, \
				line->len + 1);
	e->cursor->x = line->prev->len - 1;
	line->prev->len += line->len;
	free(line->str);
	free(line);
	--e->nb_line;
	--e->cursor->y;
}

void	delete_line(t_editor *e)
{
	t_line	*line;

	line = get_line(e, e->cursor->y);
	if (line->len == 1 && e->nb_line == 0)
		return ;
	if (line->prev)
		line->prev->next = line->next;
	else
		e->head = e->head->next;
	if (line->next)
		line->next->prev = line->prev;
	else
		--e->cursor->y;
	free(line->str);
	free(line);
	--e->nb_line;
	if (e->nb_line == 0)
		create_empty_buffer(e);
}

static void	update_list(t_line *start, t_line *end, \
				t_line *new, t_editor *e);

void	delete_selection(t_selection *sel, t_editor *e)
{
	t_line	*new;
	t_line	*start;
	t_line	*end;

	sel->is_active = 0;
	if (!is_ordered(sel->start, sel->end))
		ft_revptr((void **)&sel->start, (void **)&sel->end);
	start = get_line(e, sel->start->y);
	end = get_line(e, sel->end->y);
	ft_memmove(&start->str[sel->start->x], \
				&end->str[sel->end->x + 1], \
				ft_strlen(&end->str[sel->end->x]));
	new = new_line(start->str);
	if (!new)
		quit_free_msg("Alloc", 1, e);
	new->str[new->len] = '\n';
	new->str[++new->len] = '\0';
	update_list(start, end, new, e);
	e->cursor->x = sel->start->x;
	e->cursor->y = sel->start->y;
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
