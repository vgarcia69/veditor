/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:48:16 by v                 #+#    #+#             */
/*   Updated: 2025/03/20 21:26:29 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <termios.h>
#include <signal.h>
#include <poll.h>
#include <sys/signalfd.h>

# define YELLOW	"\033[33m"
# define BLUE	"\033[36m"
# define RESET	"\033[0m"
# define INVERT	"\033[7m"
// # define BLUE	"\033[36m"

# define INSERT 0                // Write in file
# define COMMAND 1               // Write a command
# define SINGLE 2                // Single string copied
# define MULTI 3                 // Multiple strings copied
# define SINGLE_NODE 4			 // Single string copied with \n

# define COMMAND_TEXT " -- COMMAND --"
# define INSERT_TEXT " -- INSERT --"
# define CTRL_Q '\x11'           // Quit
# define CTRL_S '\x13'           // Save
# define CTRL_C '\x03'           // Copy
# define CTRL_V '\x16'           // Paste
# define CTRL_Z '\x1A'           // Undo
# define CTRL_Y '\x19'           // Redo
# define CTRL_A '\x01'           // Go to the beginning of the line
# define CTRL_D '\x04'           // Go to the end of the line
# define CTRL_L '\x0C'           // Select the current line
# define CTRL_W '\x17'           // Select the current word
# define CTRL_X '\x18'           // Delete a line
# define BACKSPACE 127           // Delete a char
# define ESC '\x1B'              // Switch mode

# define MOUSE 'M'
# define ARROW_UP 'A'
# define ARROW_DOWN 'B'
# define ARROW_RIGHT 'C'
# define ARROW_LEFT 'D'

# define SET "set"
# define TAB_CMD "tablen"
# define LEN_CMD "length"
# define MOUSE_CMD "mouse"
# define COLOR_CMD "color"

# define NOT_FOUND "Error : Command not found"
# define EMPTY "Error : Empty command"
# define WRONG_AMONT "Error : Wrong amount of arguments"
# define WRONG_NUM "Error : Number has to be bitween 2 and 24"

typedef	struct s_line
{
	char			*str;
	int				len;
	int				capacity;
	struct s_line	*next;
	struct s_line	*prev;
}	t_line;

typedef	struct s_option 
{
	int	tablen;
	int	is_len;
	int	is_mouse;
	int	is_color;
}	t_option;

typedef struct s_cursor
{
	int	x;
	int	y;
	int	xview;
	int	yview;
}	t_cursor;

typedef struct	s_selection
{
	int			is_active;
	t_cursor	*start;	
	t_cursor	*end;	
}	t_selection;

typedef struct s_window
{
	int	height;
	int	width;
	int	start_row;
	int	start_col;
	int	tabstop;
	int	margin_left;
}	t_window;

typedef struct	s_clipboard
{
	t_line	*head;
	int 	nb_line;
	int 	type;
}	t_clipboard;

typedef struct s_display
{
	char	*content;
	int		size;
	int		capacity;
}	t_display;

typedef	struct s_data
{
	int				mode;
	int				dirty;
	int				nb_line;
	char			*f_name;
	char			*stat;
	char			*cmd;
	t_line			*head;
	t_display		*buffer;
	t_cursor		*cursor;
	t_window		*win;
	t_option		*opt;
	t_clipboard		*cpy;
	t_selection		*sel;
	struct pollfd	fd[2];
	struct termios	o_ter;
}	t_editor;

/*---------------------------UTILS--------------------------------------------*/
int		tab_align_pos(int tab_stop, int current_x);
int 	get_tabwidth(int xview, int tab_stop);
int		get_xview_from_x(t_line *line, int cursor_xview, t_window *window);
int		get_x_from_xview(t_line *line, int cursor_xview, t_window *window);
int		is_same_pos(t_cursor *p1, t_cursor *p2);
void	cp_cursor(t_cursor *dst, t_cursor *src);
int		is_ordered(t_cursor *first, t_cursor *last);
t_line	*get_line(t_editor *e, int index);
char	get_char_at(t_editor *e, int xview, int yview);
int		get_margin(t_editor *e, t_option *option);
int		len_int(int nb);
int		get_max_len(t_line *line);
time_t	get_time_ms(void);

/*---------------------------UPDATE---------------------------*/
void	update_win(t_editor *e);
void	update_vars(t_cursor *cursor, t_window *win, t_editor *e);
void	update_statbar(t_editor *e, char *str, int mode);
void	update_width(t_window *win, t_cursor *cursor, t_editor *e);

/*---------------------------ERROR---------------------------*/
void	quit_free_msg(char *str, int code, t_editor *vim);
void	quit_error_msg(char *str, int code);

/*---------------------------INIT---------------------------*/
void	init_editor(t_editor *data, char *file_name);
void	init_struct_1 \
		(t_clipboard *cpy, t_cursor *cur, t_option *opt, t_window *win);
void	init_struct_2(t_editor *e);
void	init_struct_3(t_editor *e);

int		open_file(char *file, t_editor *vim);
void	disable_raw_mode(struct termios *orig_termios);
void	enable_raw_mode(struct termios *orig_termios);

/*---------------------------BUFFER---------------------------*/
void		realloc_line(t_editor *data, t_line *line);
void		load_buffer(t_editor *data, int file);
void		free_line(t_line *lst);
void		addback_line(t_line **lst, t_line *new);
int			check_capacity(t_line *line, char *to_cat);
t_line		*new_line(char *str);
void		create_empty_buffer(t_editor *data);
void		insert_line(t_line **lst, t_line *new);

/*---------------------------PROCESS---------------------------*/
/*INPUT*/
void	process_input(t_editor *e);
void	command(t_editor *e, char *input);
void	mouse(t_editor *e, unsigned char input[3]);
void	arrow(t_editor *e, char c);
/*KEY*/
void	insert(t_editor *e, char c);
/*DELETE*/
void	delete_line(t_editor *e, t_line *line);
void	delete(t_editor *e);
void	delete_selection(t_selection *sel, t_editor *e);

/*SHORTCUT*/
void	sc_go_begin_line(t_editor *e);
void	sc_select_line(t_editor *e);
void	sc_go_end_line(t_editor *e);
void	sc_select_word(t_editor *e);
void	sc_delete_line(t_editor *e);
void	sc_save(t_editor *e);
void	sc_copy(t_editor *e);
void	sc_paste(t_editor *e);
void	sc_quit(t_editor *e);

/*SHORTCUT UTILS*/
void	clear_cpy(t_clipboard *cpy);
void	cpy_last(t_cursor *end, t_editor *e);
void	cpy_mid(t_cursor *start, t_cursor *end, t_editor *e);
void	cpy_first(t_cursor *start, t_editor *e);
void	cpy_single(int start, int end, int y, t_editor *e);
void	paste_single(t_line *line, int x, t_editor *e);
char	*paste_first(t_line *line, int x, t_editor *e);
t_line	*paste_mid(t_line *after, t_editor *e, char *carry);
void	paste_last(t_line *line, t_editor *e, char *carry);
void	cpy_node(t_line *line, t_editor *e);
void	paste_single_node(t_line *line, t_editor *e);

/*COMMAND*/
char	*tablen_cmd(t_editor *e, char *arg);
char	*mouse_cmd(t_editor *e, char *arg);
char	*lenstr_cmd(t_editor *e, char *arg);
char	*color_cmd(t_editor *e, char *arg);

/*---------------------------EDITOR---------------------------*/
void	editor_refresh_win(t_editor *e);
char	*fill_line_buffer(char *str, char *buffer, t_window *win);
char	*buffer_line(t_editor *e, t_line *line);
char	*clear_window(t_editor *e, char *buffer);
char	*add_buffer_window(t_editor *e, char *buffer);
void	draw_cursor(t_cursor *c);
void	draw_bottom(int height, char *stat, char *cmd);
char	*add_buffer_selection(t_selection *sel, t_editor *e, char *buffer);

#endif
