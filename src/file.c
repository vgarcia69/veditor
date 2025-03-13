#include "../editor.h"

int	open_file(char *file, t_editor *vim)
{
	int	fd;

	if (!file)	
		return (0);
	fd = open(file, O_RDONLY);
	if (fd == -1 && errno == 13)
		quit_free_msg("Permission Denied", 1, vim);
	return (fd);
}
