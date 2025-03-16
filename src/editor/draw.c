#include "../../editor.h"

static void	draw_tild(int i, int height);

void	draw_window(t_editor *e)
{
	t_line	*line;
	char	*count;
	int		i;

	i = 0; // set MARGIN A FAIRE (si option marign = plus grand ligne(len) + [] + nb_line plus spaces)
	line = get_line(e, e->win->start_row);
	set_margin();
	count = ft_itoa(e->nb_line);
	e->win->margin_left = ft_strlen(count) + 2;
	free(count);
	while (line && i < e->win->height)
	{
		count = ft_itoa(i);
	  	printf_fd(STDOUT_FILENO, "\033[%d;%dH%d  ", i + 1, e->win->margin_left - ft_strlen(count) - 1, i);
		draw_line(e, line);
	  	// printf_fd(STDOUT_FILENO, "\033[%d;%dH[%d]", i, e->win->width - 5, line->len - 1); a mettre en option
		line = line->next;
		free(count);
		i++;
	}
	draw_tild(i, e->win->height);
}

static void	draw_tild(int i, int height)
{
	while (i < height)
	{
	  	printf_fd(STDOUT_FILENO, "\033[%d;1H", i);
		printf_fd(STDOUT_FILENO, "~");
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
