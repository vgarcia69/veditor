#include "../../editor.h"

void enable_raw_mode(struct termios *orig_termios)
{
    struct termios	raw;

    tcgetattr(STDIN_FILENO, orig_termios);
    raw = *orig_termios;
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
	printf_fd(STDOUT_FILENO, "\033[?1002h");
	printf_fd(STDOUT_FILENO, "\033[?7l");
}

void disable_raw_mode(struct termios *orig_termios)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, orig_termios);
	printf_fd(STDOUT_FILENO, "\033[?1002l");
	printf_fd(STDOUT_FILENO, "\033[?7h");
}

void	init_struct_3(t_editor *e)
{
	t_selection		*s;
	t_display		*buffer;

	buffer = e->buffer;
	buffer->capacity = 1;
	buffer->size = 0;
	buffer->content = malloc(sizeof(char) * 1);
	if (!buffer->content)
		quit_free_msg("Alloc", 1, e);
	buffer->content[0] = 0;
	s = e->sel;
	s->end = NULL;
	s->start = NULL;
	s->start = malloc(sizeof(t_cursor));
	if (!s->start)
		quit_free_msg("Alloc", 1, e);
	s->end = malloc(sizeof(t_cursor));
	if (!s->end)
		quit_free_msg("Alloc", 1, e);
	s->is_active = 0;
	cp_cursor(e->sel->start, e->cursor);
	cp_cursor(e->sel->end, e->cursor);
}

void	init_struct_2(t_editor *e)
{
	sigset_t		mask;
	int				sigfd;

	sigemptyset(&mask);
	sigaddset(&mask, SIGWINCH);
	sigprocmask(SIG_BLOCK, &mask, NULL);
	sigfd = signalfd(-1, &mask, 0);
	if (sigfd == -1)
		quit_free_msg("Signalfd", 1, e);
	e->fd[0].fd = 0;
	e->fd[0].events = POLLIN;
	e->fd[1].fd = sigfd;
	e->fd[1].events = POLLIN;

}

void	init_struct_1 \
		(t_clipboard *copy, t_cursor *cursor, t_option *option, t_window *window)
{
	struct winsize ws;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
	{
		ws.ws_col = 96;
		ws.ws_row = 24;
	}
	window->height = ws.ws_row - 2;
	window->width = ws.ws_col;
	window->start_col = 0;
	window->start_row = 0;
	window->tabstop = 8;
	window->margin_left = 0;
	copy->head = NULL;
	copy->nb_line = 0;
	copy->type = 0;
	cursor->x = 0;
	cursor->y = 0;
	cursor->xview = 0;
	cursor->yview = 0;
	option->tablen = 8;
	option->is_len = 1;
	option->is_mouse = 1;
	option->is_color = 1;
}
