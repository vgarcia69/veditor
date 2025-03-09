/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_writenbrs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgarcia <vgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 07:23:37 by vgarcia           #+#    #+#             */
/*   Updated: 2025/03/06 17:41:49 by vgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_p(void *p, int fd)
{
	if (!p)
		return (0);
	write (fd, "0x", 2);
	return (1);
}

int	ft_printf_putmem(void *p, int fd, char *base)
{
	int					i;
	int					base_len;
	char				*str;
	unsigned long int	n;

	if (!check_p(p, fd))
		return (write(1, "(nil)", 5));
	i = 0;
	n = (unsigned long int)p;
	base_len = ft_strlen(base);
	str = malloc(sizeof(char) * (50));
	if (!str)
		return (0);
	while (n >= (unsigned long int)base_len)
	{
		str[i++] = base[n % (unsigned long int)base_len];
		n /= (unsigned long int)base_len;
	}
	str[i] = base[n % (unsigned long int)base_len];
	str[i + 1] = '\0';
	str = ft_reversestr(str, fd);
	if (str[0] == '-')
		i++;
	free(str);
	return (i + 2);
}

int	ft_printf_putnbr(int n, int fd)
{
	char	*str;
	int		i;

	str = ft_itoa(n);
	i = ft_writestr(str, fd);
	free(str);
	return (i);
}

int	ft_printf_putnbase(unsigned int n, int fd, char *base)
{
	int		i;
	int		base_len;
	char	*str;

	base_len = ft_strlen(base);
	str = malloc(sizeof(char) * (50));
	if (!str)
		return (0);
	i = 0;
	while (n >= (unsigned int)base_len)
	{
		str[i++] = base[n % base_len];
		n /= base_len;
	}
	str[i] = base[n % base_len];
	str[i + 1] = '\0';
	str = ft_reversestr(str, fd);
	if (str[0] == '-')
		i++;
	free(str);
	return (i);
}
