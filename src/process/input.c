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
	int		end;

	end = read(STDIN_FILENO, &input, 16);
	if (end == -1)
		quit_free_msg("Read function", 1, e);
	input[end] = '\0';
	if (e->mode == NORMAL)
	{
		if (input[0] == '\033')
			sequence(e, input + 1);
		else
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
	if (input[0] == '[')
	{
		if (input[1] == MOUSE)
			mouse(e, &input[2]);
		else if (input[1] >= ARROW_UP && input[1] <= ARROW_LEFT)
			arrow(e, input[1]);
	}
}
static void	keypress(t_editor *e, char input)
{
	if (input == CTRL_S) 
    	save(e);
	else if (input == CTRL_C)
		copy(e);
	else if (input == CTRL_U)
		paste(e);
	else if (input == CTRL_Z)
		undo(e);
	else if (input == CTRL_Y)
		redo(e);
	else if (input == CTRL_A)
		go_begin_line(e);
	else if (input == CTRL_D)
		go_end_line(e);
	else if (input == CTRL_L)
		select_line(e);
	else if (input == CTRL_F)
		select_word(e);
	else if (input == CTRL_X)
		delete_line(e);
	else if (input == BACKSPACE)
		delete(e);
	else
		insert(e, input);
}
