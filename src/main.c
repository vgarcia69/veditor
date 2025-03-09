#include "../editor.h"

int main(int ac, char **av)
{
	t_editor	data;

	if (ac > 2)
		return (1);
	init_editor(&data, av[1]);
	load_buffer(&data, open_file(av[1], &data));
	data.stat = "\033[7m:q PRESS to quit";
	while (1)
	{
		editor_refresh_win(&data);
		process_input(&data);
	}
	return (0);
}
