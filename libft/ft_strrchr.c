/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgarcia <vgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:16:57 by vgarcia           #+#    #+#             */
/*   Updated: 2024/11/13 09:46:39 by vgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t		i;

	i = 0;
	while (s[i])
		++i;
	while (s[i] != (unsigned char)c && i > 0)
		--i;
	if (s[i] == (unsigned char)c)
		return ((char *)&s[i]);
	return (NULL);
}
