#include "../../editor.h"

void	editor_refresh_win(t_editor *e)
{
	t_display	*buffer;

	buffer = e->buffer;
	if (wait_fps())
		return ;
	fill_window(buffer, e);
	// add_color(buffer, e);
	fill_bottom(buffer, e);
	fill_cursor(buffer, e);
	write(STDOUT_FILENO, buffer->content, buffer->size);
	ft_bzero(buffer->content, buffer->size);
	buffer->size = 0;
}
