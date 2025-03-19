#include "../editor.h"

int	open_file(char *file, t_editor *e)
{
	int	fd;

	if (!file)	
		return (0);
	fd = open(file, O_RDONLY | O_CREAT);
	if (fd == -1 && errno == 13)
		quit_free_msg("Permission Denied", 1, e);
	return (fd);
}
