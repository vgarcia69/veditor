#include "../../editor.h"

static void	create_empty_buffer(t_editor *data);
static void	add_tocat_in_buffer(t_editor *data, char *to_cat);

void	load_buffer(t_editor *data, int file)
{
	char	*to_cat;
	int		finished;

	create_empty_buffer(data);
	if (!data->f_name)
		return ;
	finished = 0;
	while (!finished)
	{
		to_cat = get_next_line(file);
		if (!to_cat)
			finished = 1;
		else
			add_tocat_in_buffer(data, to_cat);
	}
}

void	realloc_buffer(t_editor *data, t_buffer *buf)
{
	char	*new_string;

	new_string = ft_calloc(sizeof(char), buf->line->capacity * 2);
	if (!new_string)
		quit_free_msg("Alloc", 1, data);
	buf->line->capacity *= 2;
	new_string = ft_strcpy(new_string, buf->line->str);
	free(buf->line->str);
	buf->line->str = new_string;
}

static void	create_empty_buffer(t_editor *data)
{
	data->buf->head= new_line(NULL);
	if (!data->buf->head)
		quit_free_msg("Alloc", 1, data);
	data->buf->line = data->buf->head;
}

static void	add_tocat_in_buffer(t_editor *data, char *to_cat)
{
	t_line	*line;

	line = new_line(to_cat);
	if (!line)
		quit_free_msg("Alloc", 1, data);
	addback_buffer(&data->buf->line, line);
	free(to_cat);
}
