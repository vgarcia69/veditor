/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 08:26:56 by vgarcia           #+#    #+#             */
/*   Updated: 2025/03/04 16:10:08 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	isinbase(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_reversestr(char *str, int fd)
{
	char	*new_str;
	int		i;
	int		j;

	i = ft_strlen(str);
	j = 0;
	new_str = malloc(sizeof(char) * (i + 1));
	if (!new_str)
		return (NULL);
	new_str[i] = '\0';
	while (i--)
		new_str[j++] = str[i];
	free(str);
	ft_writestr(new_str, fd);
	return (new_str);
}
