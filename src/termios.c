#include "../editor.h"

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

void	init_fds(t_editor *e)
{
	sigset_t		mask;
	int				sigfd;

	sigemptyset(&mask);
	sigaddset(&mask, SIGWINCH);
	sigprocmask(SIG_BLOCK, &mask, NULL);
	sigfd = signalfd(-1, &mask, 0);
	if (sigfd == -1)
		quit_free_msg("signalfd", 1, e);
	e->fd[0].fd = 0;
	e->fd[0].events = POLLIN;
	e->fd[1].fd = sigfd;
	e->fd[1].events = POLLIN;
}

void	init_statbar(t_editor *e)
{
	ft_memset(e->stat, 32, e->win->width);
	if (e->mode == NORMAL)
		ft_memcpy(e->stat, " -- NORMAL --", 13);
	else
		ft_memcpy(e->stat, " -- COMMAND --", 14);
	if (e->f_name)
		ft_memcpy(&e->stat[20], e->f_name, ft_strlen(e->f_name));
	else
		ft_memcpy(&e->stat[20], "[NEW] - /name \"file_name\" to define it", 38);
	ft_memcpy(&e->stat[e->win->width / 2], "CTRL + Q to quit", 16);
}

void	init_selection(t_editor *e)
{
	t_selection *s;
	
	s = e->sel;
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
