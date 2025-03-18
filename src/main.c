#include "../editor.h"

int main(int ac, char **av)
{
	t_editor	data;

	if (ac > 2)
		return (1);
	init_editor(&data, ft_strdup(av[1]));
	load_buffer(&data, open_file(data.f_name, &data));
	update_all(&data);
	while (1)
	{
		editor_refresh_win(&data);
		process_input(&data);
	}
	return (0);
}
