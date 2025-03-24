#include "../../editor.h"

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

int	is_same_pos(t_cursor *p1, t_cursor *p2)
{
	if (p1->xview == p2->xview && p1->yview == p2->yview)
		return (1);
	return (0);
}

void	cp_cursor(t_cursor *dst, t_cursor *src)
{
	dst->xview = src->xview;
	dst->yview = src->yview;
	dst->x = src->x;
	dst->y= src->y;
}

int	is_ordered(t_cursor *first, t_cursor *last)
{
	if (first->yview == last->yview)
	{
		if (first->xview < last->xview)
			return (1);
	}
	else if (first->yview < last->yview)
		return (1);
	return (0);
}
