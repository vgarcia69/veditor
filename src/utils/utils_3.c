#include "../../editor.h"

int	get_margin(t_editor *e)
{
	int		size_len;
	int		size_nb;

	size_nb = len_int(e->nb_line);
	size_len = len_int(get_max_len(e->head) - 1) + 2;
	if (size_nb == -1 || size_len == -1)
		quit_free_msg("Alloc", 1, e);
	if (e->len_visu)
		return (size_nb + size_len + 3);
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

time_t	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
