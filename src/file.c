#include "../editor.h"

int	open_file(char *file, t_editor *vim)
{
	int	fd;

	if (!file)	
		return (0);
	fd = open(file, O_RDONLY);
	if (fd == -1 && errno == 13)
		quit_free_msg("Permission Denied", 1, vim);
	vim->f_name = ft_strdup(file);
	if (!vim->f_name)
		quit_free_msg("Alloc", 1, vim);
	return (fd);
}
