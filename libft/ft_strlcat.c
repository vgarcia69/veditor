/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgarcia <vgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:23:33 by vgarcia           #+#    #+#             */
/*   Updated: 2025/02/11 10:00:52 by vgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;

	i = 0;
	dstlen = 0;
	srclen = 0;
	while (dst[dstlen])
		++dstlen;
	while (src[srclen])
		++srclen;
	if (dstlen >= size)
		return (size + srclen);
	while (dstlen < size - i - 1 && src[i])
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	return (dstlen + srclen);
}

char	*ft_strcat(char *dst, const char *src)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (dst[i])
		++i;
	while (src[++j])
		dst[i + j] = src[j];
	dst[i + j] = '\0';
	return (dst);
}
