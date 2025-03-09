/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincentgarcia <vincentgarcia@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:26:22 by vincentgarc       #+#    #+#             */
/*   Updated: 2024/11/12 14:00:18 by vincentgarc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	char	n;

	n = '\n';
	while (*s)
		write(fd, s++, 1);
	write(fd, &n, 1);
}
