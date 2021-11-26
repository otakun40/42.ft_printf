/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacoby <pjacoby@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:08:55 by pjacoby           #+#    #+#             */
/*   Updated: 2021/11/26 22:53:55 by pjacoby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *fm, ...)
{
	va_list	ap;
	int		printed;

	printed = 0;
	va_start(ap, fm);
	while (*fm)
	{
		if (*fm != '%')
			printed += (int)write(1, fm, 1);
		else
		{
			fm++;
			if (*(fm) == '%')
				printed += (int) write(1, "%", 1);
			if (*(fm) == 'p' || *(fm) == 's' || *(fm) == 'u' || *(fm) == 'c'
				|| *(fm) == 'x' || *(fm) == 'X' || *(fm) == 'd' || *(fm) == 'i')
				printed += spec_handler(*(fm), ap);
		}
		fm++;
	}
	va_end(ap);
	return (printed);
}
