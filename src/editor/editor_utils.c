#include "../../editor.h"

void	append_string(t_display *buffer, t_editor *e, char *string, ...)
{
	char	*new_content;
	int		string_size;
	va_list	args;
	va_list	cpy_args;

	va_start(args, string);
	va_copy(cpy_args, args);
	string_size = vsnprintf(NULL, 0, string, cpy_args);
	while (string_size + buffer->size >= buffer->capacity)
	{
		new_content = ft_calloc(sizeof(char), buffer->capacity*2);
		if (!new_content)
			quit_free_msg("Alloc", 1, e);
		ft_strcat(new_content, buffer->content);
		free(buffer->content);
		buffer->content = new_content;
		buffer->capacity *= 2;
	}
	buffer->size += vsprintf(buffer->content + buffer->size, string, args);
	va_end(args);
	va_end(cpy_args);
}

static time_t	get_time_ms(void);

int	wait_fps(void)
{
	static time_t	last_frame_time;
	time_t			current_time;

	current_time = get_time_ms();
	if (current_time - last_frame_time < 40)
		return (1);
	last_frame_time = current_time;
	return (0);
}

static time_t	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
