/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgarcia <vgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:51:58 by vgarcia           #+#    #+#             */
/*   Updated: 2025/02/17 11:56:43 by vgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*result;
	int		slen;

	slen = 0;
	if (!s)
		return (NULL);
	while (s[slen])
		++slen;
	result = malloc(sizeof(char) * slen + 1);
	if (result == NULL)
		return (NULL);
	slen = 0;
	while (*s)
		result[slen++] = *s++;
	result[slen] = '\0';
	return (result);
}
