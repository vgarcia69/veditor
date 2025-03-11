#ifndef EDITOR_H
# define EDITOR_H

#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <signal.h>
#include <poll.h>
#include <sys/signalfd.h>

# define NORMAL 0
# define COMMAND 1

typedef	struct s_line
{
	char			*str;
	int				len;
	int				capacity;
	struct s_line	*next;
	struct s_line	*prev;
}	t_line;

typedef struct s_buffer
{
	int		nbr_line;
	t_line	*head;
}	t_buffer;

typedef struct s_cursor
{
	int	x;
	int	y;
	int	xview;
	int	yview;
}	t_cursor;

typedef struct s_window
{
	int	height;
	int	width;
	int	starting_row;
	int	starting_col;
}	t_window;

typedef	struct s_data
{
	int				dirty;
	int				tab_stop;
	int				mode;
	char			*f_name;
	char			*clip_board;
	char			*stat;
	char			*cmd;
	t_cursor		*cursor;
	t_buffer		*buf;
	t_window		*win;
	struct pollfd	fd[2];
	struct termios	o_ter;
}	t_editor;

/*---------------------------UTILS---------------------------*/
int		tab_align_pos(int tab_stop, int current_x);
int 	get_tabwidth(int xview, int tab_stop);
int		get_x_from_xview(t_line *line, int cursor_xview, int tab_stop, int s_col);
int		get_xview_from_x(t_line *line, int cursor_x, int tab_stop, int s_col);
t_line	*get_line(t_editor *e, int index);
int		is_same_pos(t_cursor *p1, t_cursor *p2);
void	highlight(t_editor *e, t_cursor *pp, t_cursor *ip);

/*---------------------------ERROR---------------------------*/
void	quit_free_msg(char *str, int code, t_editor *vim);
void	quit_error_msg(char *str, int code);
void	print_err(char *str);

/*---------------------------INIT---------------------------*/
void	init_editor(t_editor *data, char *file_name);
void	disable_raw_mode(struct termios *orig_termios);
void	enable_raw_mode(struct termios *orig_termios);
void	init_fds(t_editor *e);

/*---------------------------FILE---------------------------*/
int		open_file(char *file, t_editor *vim);

/*---------------------------BUFFER---------------------------*/
void		realloc_line(t_editor *data, t_line *line);
void		load_buffer(t_editor *data, int file);
void		free_line(t_line *lst);
void		addback_line(t_line **lst, t_line *new);
int			check_capacity(t_line *line, char *to_cat);
t_line		*new_line(char *str);

/*---------------------------PROCESS---------------------------*/
void	process_input(t_editor *e);
void	command(t_editor *e, char *input);
void	mouse(t_editor *e, char input[2]);
void	arrow(t_editor *e, char c);
/*KEY*/
void	insert(t_editor *e, char c);
void	delete(t_editor *e);

/*SHORTCUT*/
void	select_all(t_editor *e);
void	select_line(t_editor *e);
void	duplicate_line(t_editor *e);
void	search(t_editor *e);
void	delete_line(t_editor *e);
void	save(t_editor *e);
void	copy_clip_board(t_editor *e);
void	paste_clip_board(t_editor *e);
void	undo(t_editor *e);
void	redo(t_editor *e);

/*---------------------------EDITOR---------------------------*/
void	editor_refresh_win(t_editor *e);
void	draw_window(t_editor *e);
void	draw_cursor(t_cursor *c);
void	draw_status(int height, char *stat, int mode);
void	draw_command(int height, char *cmd);
void	draw_line(t_editor *e, t_line *line);

#endif
