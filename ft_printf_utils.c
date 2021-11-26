/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacoby <pjacoby@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 22:58:53 by pjacoby           #+#    #+#             */
/*   Updated: 2021/11/26 23:01:55 by pjacoby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	ft_putstr(char *str)
{
	int	count;

	count = 0;
	if (!str)
		return ((int)write(1, "(null)", 6));
	while (*str)
		count += (int)write(1, str++, 1);
	return (count);
}

static int	ft_putnbr_base(long nbr, char *base)
{
	char		c;
	int			minus;
	int			base_len;
	static int	digit_count;

	minus = 0;
	digit_count = 0;
	base_len = ft_strlen(base);
	if (nbr < 0)
	{
		minus = 1;
		write(1, "-", 1);
		nbr *= -1;
	}
	if (nbr / base_len)
		ft_putnbr_base(nbr / base_len, base);
	c = base[nbr % base_len];
	digit_count += (int)write(1, &c, 1);
	if (minus)
		digit_count++;
	return (digit_count);
}

static int	ft_put_pntr(unsigned long nbr, char *base)
{
	char		c;
	static int	digit_count;

	digit_count = 0;
	if (nbr / 16)
		ft_put_pntr(nbr / 16, base);
	c = base[nbr % 16];
	digit_count += (int)write(1, &c, 1);
	return (digit_count);
}

int	spec_handler(char spec, va_list arg)
{
	int		printed;
	char	c;

	printed = 0;
	if (spec == 'c')
	{
		c = va_arg(arg, int);
		printed = (int)write(1, &c, 1);
	}
	if (spec == 's')
		printed = ft_putstr(va_arg(arg, char *));
	if (spec == 'd' || spec == 'i')
		printed = ft_putnbr_base(va_arg(arg, int), "0123456789");
	if (spec == 'u')
		printed = ft_putnbr_base(va_arg(arg, unsigned int), "0123456789");
	if (spec == 'x')
		printed = ft_putnbr_base(va_arg(arg, unsigned int), "0123456789abcdef");
	if (spec == 'X')
		printed = ft_putnbr_base(va_arg(arg, unsigned int), "0123456789ABCDEF");
	if (spec == 'p')
	{
		printed = (int)write(1, "0x", 2);
		printed += ft_put_pntr(va_arg(arg, long), "0123456789abcdef");
	}
	return (printed);
}
