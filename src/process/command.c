
#include "../../editor.h"

/*
buffer command quand \n send et empty it
*/

/*
raccourcis en cmd

/name file
/tp
/doc
/tabstop
*/
static void	delete_cmd(t_editor *e, char *cmd);
static void	insert_cmd(t_editor *e, char *cmd, char c);
static void	send_command(t_editor *e, char *cmd);

void	command(t_editor *e, char *input)
{
	if (input[1])
		return ;
	else if (input[0] == '\r' || input[0] == '\n')
	{
		send_command(e, e->cmd);
		e->cmd[0] = '\0';
	}
	else if (ft_isualnum(input[0]) || input[0] == ' ')
		insert_cmd(e, e->cmd, input[0]);
	else if (input[0] == BACKSPACE)
		delete_cmd(e, e->cmd);
	else if (input[0] == ESC)
		update_statbar(e, "Insert mode activated", INSERT);
	else if (input[0] == CTRL_Q)
		sc_quit(e);
}

static void	delete_cmd(t_editor *e, char *cmd)
{
	int	len_cmd;

	len_cmd = ft_strlen(cmd);
	if (!len_cmd)
		update_statbar(e, "No chars to delete", -1);
	else
		cmd[len_cmd - 1] = '\0';
}

static void	insert_cmd(t_editor *e, char *cmd, char c)
{
	int	len_cmd;

	len_cmd = ft_strlen(cmd);
	if (len_cmd >= 255)
		update_statbar(e, "Error : Too many chars in Command", -1);
	else
	{
		cmd[len_cmd] = c;
		cmd[len_cmd + 1] = '\0';
	}
}

static void	send_command(t_editor *e, char *cmd)
{
	char	**cmd_args;
	int		i;

	i = 0;
	if (!*cmd)
		return (update_statbar(e, EMPTY, -1));
	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
		quit_free_msg("Alloc", 1, e);
	while (cmd_args[i])
		i++;
	if (i != 3)
		return (update_statbar(e, WRONG_AMONT, -1));
	if (ft_strcmp(cmd_args[0], SET))
		return (update_statbar(e, NOT_FOUND, -1));
	if (!ft_strcmp(cmd_args[1], TAB_CMD))
		update_statbar(e, tablen_cmd(e, cmd_args[2]), INSERT);
	else if (!ft_strcmp(cmd_args[1], MOUSE_CMD))
		update_statbar(e, mouse_cmd(e, cmd_args[2]), INSERT);
	else if (!ft_strcmp(cmd_args[1], LEN_CMD))
		update_statbar(e, lenstr_cmd(e, cmd_args[2]), INSERT);
	else if (!ft_strcmp(cmd_args[1], COLOR_CMD))
		update_statbar(e, color_cmd(e, cmd_args[2]), INSERT);
	else
		update_statbar(e, NOT_FOUND, -1);
}
