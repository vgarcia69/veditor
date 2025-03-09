/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:12:30 by vincentgarc       #+#    #+#             */
/*   Updated: 2025/03/04 16:07:46 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_printarg(va_list arg, char c, int fd)
{
	if (c == 'c')
		return (ft_writechar(va_arg(arg, int), fd));
	else if (c == 's')
		return (ft_writestr(va_arg(arg, char *), fd));
	else if (c == 'p')
		return (ft_printf_putmem(va_arg(arg, void *), fd,
				"0123456789abcdef"));
	else if (c == 'd')
		return (ft_printf_putnbr(va_arg(arg, int), fd));
	else if (c == 'i')
		return (ft_printf_putnbr(va_arg(arg, int), fd));
	else if (c == 'u')
		return (ft_printf_putnbase(va_arg(arg, unsigned int), fd,
				"0123456789"));
	else if (c == 'x')
		return (ft_printf_putnbase(va_arg(arg, unsigned int), fd,
				"0123456789abcdef"));
	else if (c == 'X')
		return (ft_printf_putnbase(va_arg(arg, unsigned int), fd,
				"0123456789ABCDEF"));
	else if (c == '%')
		return (write(1, "%", 1));
	return (0);
}

int	printf_fd(int fd, const char *a, ...)
{
	va_list	args;
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (!a)
		return (-1);
	va_start(args, a);
	while (a[i])
	{
		if (a[i] == '%' && isinbase(a[i + 1], "cspdiuxX%"))
		{
			len += ft_printarg(args, a[i + 1], fd);
			i += 2;
		}
		else
			len += write (fd, &a[i++], 1);
	}
	va_end(args);
	return (len);
}
