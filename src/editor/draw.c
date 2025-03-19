/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgarcia <vgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:19:52 by vgarcia           #+#    #+#             */
/*   Updated: 2025/03/19 16:34:56 by vgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../editor.h"

static void	draw_tild(int i, int height);
static void	draw_border(t_editor *e, t_line *line, int i, int max_len);

void	draw_window(t_editor *e)
{
	t_line	*line;
	int		max_len;
	int		i;

	i = 0;
	line = get_line(e, e->win->start_row);
	max_len = 0;
	if (e->opt->draw_strlen)
	{
		max_len = len_int(get_max_len(e->head) - 1);
		if (max_len == -1)
			quit_free_msg("Alloc", 1, e);
	}
	while (line && i < e->win->height)
	{
		draw_border(e, line, i + 1, max_len);
		draw_line(e, line);
		line = line->next;
		i++;
	}
	draw_tild(i + 1, e->win->height + 1);
}

static void	draw_border(t_editor *e, t_line *line, int i, int max_len)
{
	int	x_viewi;
	int	x_viewlen;
	int option;
	int	margin;

	option = 0;
	if (e->opt->draw_strlen)
		option = 1;
	margin = get_margin(e, e->opt);
	x_viewi = margin - len_int(i + e->win->start_row) - max_len - option*3;
	x_viewlen = margin - len_int(line->len - 1) - 2;
	printf_fd(STDOUT_FILENO, "\033[%d;%dH", i, x_viewi);
	printf_fd(STDOUT_FILENO, YELLOW"%d"RESET, i + e->win->start_row);
	if (e->opt->draw_strlen)
	{
		printf_fd(STDOUT_FILENO, "\033[%d;%dH", i, x_viewlen);
		printf_fd(STDOUT_FILENO, "["BLUE"%d"RESET"]", line->len - 1);
	}
	printf_fd(STDOUT_FILENO, "\033[%d;%dH", i, margin + 1);
}

static void	draw_tild(int i, int height)
{
	while (i < height)
	{
	  	printf_fd(STDOUT_FILENO, "\033[%d;1H", i);
		printf_fd(STDOUT_FILENO, BLUE"~"RESET);
		i++;
	}
}

void	draw_cursor(t_cursor *c)
{
	printf_fd(STDOUT_FILENO, "\033[%d;%dH", c->yview + 1, c->xview + 1);
	printf_fd(STDOUT_FILENO, "\033[7m");
	printf_fd(STDOUT_FILENO, "\033[%d;%dH", c->yview + 1, c->xview + 1);
	printf_fd(STDOUT_FILENO, "\033[0m");
}

void	draw_bottom(int height, char *stat, int mode, char *cmd)
{
	printf_fd(STDOUT_FILENO, "\033[%d;1H\033[1;7m", height + 1);
	printf_fd(STDOUT_FILENO, "%s", stat);
	printf_fd(STDOUT_FILENO, "\033[%d;1H\033[0m", height + 2);
	printf_fd(STDOUT_FILENO, "\033[%d;1H", height + 3);
	printf_fd(STDOUT_FILENO, "%s", cmd);
}

/* initialiser i a cursor Y ??*/
