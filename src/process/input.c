#include "../../editor.h"

static void	sequence(t_editor *e, char *input);
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
	char	input[16];
	int		input_len;

	input_len = read(STDIN_FILENO, &input, 16);
	if (input_len == -1)
		quit_free_msg("Read function", 1, e);
	input[input_len] = '\0';
	if (e->mode == NORMAL)
	{
		if (input[0] == '\033')
			sequence(e, input + 1);
		else if (input_len == 1)
    		keypress(e, input[0]);
	}
	else
		command(e, input);
}

static void	read_signal(t_editor *e)
{
	struct signalfd_siginfo siginfo;
	int						secure;

	secure = read(e->fd[1].fd, &siginfo, sizeof(siginfo)); 
	if (secure == -1)
		quit_free_msg("Read function", 1, e);
}

static void	sequence(t_editor *e, char *input)
{
	t_line	*line;

	if (input[0] == '[')
	{
		if (input[1] == MOUSE)
			mouse(e, &input[2]);
		else if (input[1] >= ARROW_UP && input[1] <= ARROW_LEFT)
		{
			arrow(e, input[1]);
			line = get_line(e, e->cursor->y);
			update_scroll(e->cursor, line, e->win, e->nb_line);
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
	else if (input == CTRL_U)
		sc_paste(e);
	else if (input == CTRL_Z)
		sc_undo(e);
	else if (input == CTRL_Y)
		sc_redo(e);
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
	else
		insert(e, input);
}
