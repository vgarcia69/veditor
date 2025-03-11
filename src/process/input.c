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
		quit_free_msg("poll", 1, e);	
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
		else if (end == 1)
			keypress(e, input[0]);
	}
	else
		command(e, input);
}

static void	read_signal(t_editor *e)
{
	int						secure;
	struct signalfd_siginfo siginfo;

	secure = read(e->fd[1].fd, &siginfo, sizeof(siginfo)); 
	if (secure > 0)
	{
		if (siginfo.ssi_signo == SIGWINCH)
			editor_refresh_win(e);
	}
	printf_fd(2, "signal !\n");
}

static void	sequence(t_editor *e, char *input)
{
	if (input[0] == '[')
	{
		if (input[1] == 'M')
			mouse(e, &input[2]);
		else if (input[1] >= 'A' && input[1] <= 'D')
			arrow(e, input[1]);
	}
}

static void	keypress(t_editor *e, char input)
{
	if (input == '\x13') 
    	save(e);
	else if (input == '\x18')
		delete_line(e);
	else if (input == '\x03')
		copy_clip_board(e);
	else if (input == '\x15')
		paste_clip_board(e);
	else if (input == '\x1A')
		undo(e);
	else if (input == '\x19')
		redo(e);
	else if (input == '\x01')
		select_all(e);
	else if (input == '\x0C')
		select_line(e);
	else if (input == '\x04')
		duplicate_line(e);
	else if (input == '\x06')
		search(e);
	else if (input == 127)
		delete(e);
	else
		insert(e, input);
}
