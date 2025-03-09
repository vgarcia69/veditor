/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgarcia <vgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:17:08 by vgarcia           #+#    #+#             */
/*   Updated: 2024/11/13 09:52:44 by vgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	set_max_min(size_t *max_s1, char const *s1, char const *set)
{
	unsigned short int	t;
	size_t				i;
	size_t				min_s1;

	min_s1 = 0;
	t = 0;
	while (!t)
	{
		i = 0;
		t = 1;
		while (set[i] && min_s1 < *max_s1)
		{
			if (s1[min_s1] == set[i] || s1[*max_s1 - 1] == set[i])
			{
				if (s1[*max_s1 - 1] == set[i])
					--(*max_s1);
				if (s1[min_s1] == set[i])
					++min_s1;
				t = 0;
			}
			i++;
		}
	}
	return (min_s1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*str;
	size_t			max_s1;
	size_t			min_s1;
	size_t			i;

	max_s1 = 0;
	min_s1 = 0;
	while (s1[max_s1])
		++max_s1;
	i = 0;
	min_s1 = set_max_min(&max_s1, s1, set);
	if (max_s1 < min_s1)
		max_s1 = min_s1;
	str = malloc (sizeof(char) * (max_s1 - min_s1) + 1);
	if (!str)
		return (NULL);
	while (min_s1 < max_s1)
		str[i++] = s1[min_s1++];
	str[i] = '\0';
	return (str);
}
