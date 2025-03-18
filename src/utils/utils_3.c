#include "../../editor.h"

int get_max_len(t_line *line);

int	get_margin(t_editor *e, t_option *option)
{
	int		size_len;
	int		size_nb;

	size_nb = len_int(e->nb_line);
	size_len = len_int(get_max_len(e->head) - 1);
	if (size_nb == -1 || size_len == -1)
		quit_free_msg("Alloc", 1, e);
	if (option->draw_strlen)
		return (size_nb + size_len + 5);
	return (size_nb + 2);
}

int	len_int(int nb)
{
	int		len;
	char	*nb_str;

	len = 0;
	nb_str = ft_itoa(nb);
	if (!nb_str)
		return (-1);
	len = ft_strlen(nb_str);
	free(nb_str);
	return (len);
}

int get_max_len(t_line *line)
{
	int	max;

	max = 0;
	while (line)
	{
		if (line->len > max)
			max = line->len;
		line = line->next;
	}
	return (max);
}
