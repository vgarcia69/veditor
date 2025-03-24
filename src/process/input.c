#include "../../editor.h"

static void	sequence(t_editor *e, unsigned char *input);
static void	keypress(t_editor *e, char input);
static void	read_input(t_editor *e);
static void	read_signal(t_editor *e);

void	process_input(t_editor *e)
{
	int	secure;	

	secure = poll(e->fd, 2, -1);
	if (secure == -1)
		quit_free_msg("Poll function", 1, e);	
	else if (e->fd[0].revents & POLLIN)
		read_input(e);
	else if (e->fd[1].revents & POLLIN)
		read_signal(e);
}

static void	read_input(t_editor *e)
{
	unsigned char	input[16];
	int		input_len;

	input_len = read(STDIN_FILENO, &input, 16);
	if (input_len == -1)
		quit_free_msg("Read function", 1, e);
	input[input_len] = '\0';
	if (e->mode == INSERT)
	{
		if (input[0] == ESC && input[1])
			sequence(e, input + 1);
		else if (input_len == 1)
    		keypress(e, input[0]);
	}
	else
		command(e, (char *)input);
}

static void	read_signal(t_editor *e)
{
	struct signalfd_siginfo siginfo;
	struct winsize			ws;
	int						secure;

	secure = read(e->fd[1].fd, &siginfo, sizeof(siginfo)); 
	if (secure == -1)
		quit_free_msg("Read function", 1, e);
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) != -1)
	{
		e->win->height = ws.ws_row - 2;
		e->win->width = ws.ws_col;
	}
	update_statbar(e, NULL, -1);
}

static void	sequence(t_editor *e, unsigned char *input)
{
	if (input[0] == '[')
	{
		if (input[1] == MOUSE)
		{
			mouse(e, &input[2]);
			update_vars(e->cursor, e->win, e);
			update_width(e->win, e->cursor, e);	
		}
		else if (input[1] >= ARROW_UP && input[1] <= ARROW_LEFT)
		{
			arrow(e, input[1]);
			update_win(e);
		}
	}
}

static void	keypress(t_editor *e, char input)
{
	if (input == CTRL_S) 
		sc_save(e);
	else if (input == CTRL_Q)
		sc_quit(e);
	else if (input == CTRL_C)
		sc_copy(e);
	else if (input == CTRL_V)
		sc_paste(e);
	else if (input == CTRL_A)
		sc_go_begin_line(e);
	else if (input == CTRL_D)
		sc_go_end_line(e);
	else if (input == CTRL_L)
		sc_select_line(e);
	else if (input == CTRL_W)
		sc_select_word(e);
	else if (input == CTRL_X)
		sc_delete_line(e);
	else if (input == BACKSPACE)
		delete(e);
	else if (ft_isprint(input))
		insert(e, input);
	else if (input == ESC)
		update_statbar(e, "Command mode activated", COMMAND);
	update_win(e);
}
