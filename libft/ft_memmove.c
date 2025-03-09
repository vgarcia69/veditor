/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgarcia <vgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:14:19 by vgarcia           #+#    #+#             */
/*   Updated: 2024/11/13 09:39:52 by vgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest2;
	unsigned char	*src2;

	if (dest == NULL && src == NULL)
		return (NULL);
	dest2 = (unsigned char *)dest;
	src2 = (unsigned char *)src;
	if (src2 < dest2 && dest2 < src2 + n)
	{
		dest2 += n - 1;
		src2 += n - 1;
		while (n--)
			*dest2-- = *src2--;
	}
	else
		while (n--)
			*dest2++ = *src2++;
	return (dest);
}
