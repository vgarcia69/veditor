#include "../editor.h"

static void	add_tocat_in_buffer(t_editor *data, char *to_cat);

void	load_buffer(t_editor *e, int file)
{
	char	*to_cat;
	int		finished;

	if (!e->f_name)
	{
		create_empty_buffer(e);
		e->nb_line = 1;
		return ;
	}
	finished = 0;
	while (!finished)
	{
		to_cat = get_next_line(file);
		if (!to_cat)
			finished = 1;
		else
			add_tocat_in_buffer(e, to_cat);
	}
	close(file);
}

void	realloc_line(t_editor *data, t_line *line)
{
	char	*new_string;

	new_string = ft_calloc(sizeof(char), line->capacity * 2);
	if (!new_string)
		quit_free_msg("Alloc", 1, data);
	line->capacity *= 2;
	new_string = ft_strcpy(new_string, line->str);
	free(line->str);
	line->str = new_string;
}

void	create_empty_buffer(t_editor *data)
{
	data->head = new_line(NULL);
	if (!data->head)
		quit_free_msg("Alloc", 1, data);
}

static void	add_tocat_in_buffer(t_editor *data, char *to_cat)
{
	t_line	*head;

	head = new_line(to_cat);
	if (!head)
		quit_free_msg("Alloc", 1, data);
	addback_line(&data->head, head);
	++data->nb_line;
	free(to_cat);
}
