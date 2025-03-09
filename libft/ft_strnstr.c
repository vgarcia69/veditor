/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgarcia <vgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:52:01 by vgarcia           #+#    #+#             */
/*   Updated: 2024/11/13 09:48:11 by vgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	size_little;

	size_little = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (little[size_little])
		++size_little;
	i = 0;
	while (big[i])
	{
		j = 0;
		while (i + j < len && big[i + j] == little[j])
		{
			if (j == size_little - 1)
				return ((char *)&big[i]);
			++j;
		}
		++i;
	}
	return (NULL);
}
