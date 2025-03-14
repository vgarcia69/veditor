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

# define NORMAL 0                // Write in file
# define COMMAND 1               // Write a command
# define CTRL_Q '\x11'           // Quit
# define CTRL_S '\x13'           // Save
# define CTRL_C '\x03'           // Copy
# define CTRL_U '\x15'           // Paste
# define CTRL_Z '\x1A'           // Undo
# define CTRL_Y '\x19'           // Redo
# define CTRL_A '\x01'           // Go to the beginning of the line
# define CTRL_D '\x04'           // Go to the end of the line
# define CTRL_L '\x0C'           // Select the current line
# define CTRL_W '\x17'           // Select the current word
# define CTRL_X '\x18'           // Delete a line
# define BACKSPACE 127           // Delete a char

# define MOUSE 'M'
# define ARROW_UP 'A'
# define ARROW_DOWN 'B'
# define ARROW_RIGHT 'C'
# define ARROW_LEFT 'D'

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
}	t_buffer;

typedef struct s_cursor
{
	int	x;
	int	y;
	int	xview;
	int	yview;
}	t_cursor;

typedef struct	s_selection
{
	t_cursor *start;	
	t_cursor *end;	
	int is_active;
}	t_selection;

typedef struct s_window
{
	int	height;
	int	width;
	int	start_row;
	int	start_col;
	int	tabstop;
}	t_window;

typedef	struct s_data
{
	int				mode;
	int				dirty;
	char			*f_name;
	char			*clip_board;
	char			*stat;
	char			*cmd;
	int				nb_line;
	t_line			*head;
	t_cursor		*cursor;
	t_window		*win;
	t_selection		*sel;
	struct pollfd	fd[2];
	struct termios	o_ter;
}	t_editor;

/*---------------------------UTILS---------------------------*/
int		tab_align_pos(int tab_stop, int current_x);
int 	get_tabwidth(int xview, int tab_stop);
int		get_xview_from_x(t_line *line, int cursor_xview, t_window *window);
int		get_x_from_xview(t_line *line, int cursor_xview, t_window *window);
int		is_same_pos(t_cursor *p1, t_cursor *p2);
void	cp_cursor(t_cursor *dst, t_cursor *src);
int		is_ordered(t_cursor *first, t_cursor *last);
t_line	*get_line(t_editor *e, int index);
char	get_char_at(t_editor *e, int xview, int yview);

/*---------------------------ERROR---------------------------*/
void	quit_free_msg(char *str, int code, t_editor *vim);
void	quit_error_msg(char *str, int code);

/*---------------------------INIT---------------------------*/
void	init_editor(t_editor *data, char *file_name);
void	disable_raw_mode(struct termios *orig_termios);
void	enable_raw_mode(struct termios *orig_termios);
void	init_fds(t_editor *e);
void	init_statbar(t_editor *e);
void	init_selection(t_editor *e);

/*---------------------------FILE---------------------------*/
int		open_file(char *file, t_editor *vim);

/*---------------------------BUFFER---------------------------*/
void		realloc_line(t_editor *data, t_line *line);
void		load_buffer(t_editor *data, int file);
void		free_line(t_line *lst);
void		addback_line(t_line **lst, t_line *new);
int			check_capacity(t_line *line, char *to_cat);
t_line		*new_line(char *str);
void		create_empty_buffer(t_editor *data);

/*---------------------------PROCESS---------------------------*/
/*INPUT*/
void	process_input(t_editor *e);
void	command(t_editor *e, char *input);
void	mouse(t_editor *e, char input[3]);
void	arrow(t_editor *e, char c);
/*KEY*/
void	insert(t_editor *e, char c);
void	delete(t_editor *e);

/*SHORTCUT*/
void	go_begin_line(t_editor *e);
void	select_line(t_editor *e);
void	go_end_line(t_editor *e);
void	select_word(t_editor *e);
void	delete_line(t_editor *e);
void	save(t_editor *e);
void	copy(t_editor *e);
void	paste(t_editor *e);
void	undo(t_editor *e);
void	redo(t_editor *e);
void	quit(t_editor *e);

/*---------------------------EDITOR---------------------------*/
/*REFRESH*/
void	editor_refresh_win(t_editor *e);

/*DRAW*/
void	draw_window(t_editor *e);
void	draw_cursor(t_cursor *c);
void	draw_bottom(int height, char *stat, int mode, char *cmd);
void	draw_line(t_editor *e, t_line *line);
void	draw_selection(t_selection *sel, t_editor *e);

#endif
