/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgarcia <vgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:06:19 by vgarcia           #+#    #+#             */
/*   Updated: 2024/11/13 09:39:12 by vgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*t;

	if (dest == NULL && src == NULL)
		return (NULL);
	t = (char *)dest;
	while (n--)
		*(char *)dest++ = *(char *)src++;
	return (t);
}
