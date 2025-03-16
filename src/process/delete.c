/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:46:14 by v                 #+#    #+#             */
/*   Updated: 2025/03/16 13:56:52 by v                ###   ########.fr       */
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
	else if (e->cursor->xview == e->win->margin_left)
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
