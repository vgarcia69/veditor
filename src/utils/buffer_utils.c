#include "../../editor.h"

t_line	*new_line(char *str)
{
	t_line	*new_list;
	int		str_len;

	if (!str)
		str_len = 1;
	else
		str_len = ft_strlen(str);
	new_list = malloc(sizeof(t_line));
	if (!new_list)
		return (NULL);
	new_list->str = ft_calloc(sizeof(char), str_len * 2 + 128);
	if (!new_list->str)
	{
		free(new_list);
		return (NULL);
	}
	new_list->str = ft_strcpy(new_list->str, str);
	if (!*new_list->str)
		ft_strcpy(new_list->str, "\n");
	new_list->capacity = str_len * 2 + 128;
	new_list->len = str_len;
	new_list->next = NULL;
	new_list->prev = NULL;
	return (new_list);
}

void	addback_line(t_line **lst, t_line *new)
{
	t_line	*temp;

	temp = *lst;
	if (!*lst)
		*lst = new;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
}

void	free_line(t_line *lst)
{
	t_line	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		if (tmp->str)
			free(tmp->str);
		free(tmp);
	}
}

int	check_capacity(t_line *line, char *to_cat)
{
	int	len_tocat;
	int	len_bufferstring;

	len_tocat = ft_strlen(to_cat);
	len_bufferstring = ft_strlen(line->str);	
	if (line->capacity <= len_bufferstring + len_tocat)
		return (0);
	return (1);
}

void	insert_line(t_line **lst, t_line *new)
{
	if (!*lst)
		*lst = new;
	else
	{
		new->next = (*lst)->next;
		new->prev = *lst;
		(*lst)->next = new;
		if (new->next)
			new->next->prev = new;
	}
}
