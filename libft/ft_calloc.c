/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgarcia <vgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:58:26 by vgarcia           #+#    #+#             */
/*   Updated: 2024/11/13 11:22:05 by vgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	i;
	size_t	total;

	total = nmemb * size;
	if (size && nmemb)
		if (size > (size_t) - 1 / nmemb)
			return (NULL);
	i = 0;
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	while (total--)
	{
		*(char *)ptr++ = 0;
		i++;
	}
	while (i--)
		ptr--;
	return (ptr);
}
