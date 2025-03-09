/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgarcia <vgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:59:21 by vgarcia           #+#    #+#             */
/*   Updated: 2024/11/13 09:53:42 by vgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_numbers(long int n)
{
	size_t	i;

	i = 0;
	if (n < 0)
	{
		++i;
		n = -n;
	}
	while (n > 9)
	{
		n /= 10;
		++i;
	}
	++i;
	return (i);
}

char	*ft_itoa(int n)
{
	char			*str;
	size_t			i;
	long int		n2;

	n2 = n;
	i = count_numbers(n2);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	if (n2 < 0)
	{
		str[0] = '-';
		str[i--] = '\0';
		n2 = -n2;
	}
	else
		str[i--] = '\0';
	while (n2 > 9)
	{
		str[i--] = n2 % 10 + 48;
		n2 /= 10;
	}
	str[i] = n2 + 48;
	return (str);
}
