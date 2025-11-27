/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvolikov <pvolikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 23:12:16 by pvolikov          #+#    #+#             */
/*   Updated: 2025/08/12 15:02:06 by pvolikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include <libft.h>
#include "ft_printf.h"
//#include "libft/libft.h"

static int	do_conversion_nb(va_list args, t_prtfconv cnv)
{
	long int	i;
	char		*s;
	int			len;

	if (cnv.type == 'd' || cnv.type == 'i')
	{
		i = va_arg(args, int);
		s = ft_itoa(i);
		len = ft_strlen(s);
		return (free(s), ft_putnbr_fd(i, 1), len);
	}
	else if (cnv.type == 'u')
		return (ft_nputunbr_fd(va_arg(args, unsigned int), 1));
	else if (cnv.type == 'x')
		return (ft_nputunbr_base_fd(va_arg(args, unsigned int),
				"0123456789abcdef", 1));
	else if (cnv.type == 'X')
		return (ft_nputunbr_base_fd(va_arg(args, unsigned int),
				"0123456789ABCDEF", 1));
	else
		return (-1000);
}

static int	do_conversion_misc(va_list args, t_prtfconv cnv)
{
	char			*s;
	unsigned long	p;

	if (cnv.type == 'c')
		return (ft_nputchar_fd(va_arg(args, int), 1));
	else if (cnv.type == 's')
	{
		s = va_arg(args, char *);
		if (!s)
			s = "(null)";
		return (ft_putstr_fd(s, 1), ft_strlen(s));
	}
	else if (cnv.type == 'p')
	{
		p = va_arg(args, unsigned long);
		if (!p)
			return (s = "(nil)", ft_putstr_fd(s, 1), ft_strlen(s));
		return (ft_nputstr_fd("0x", 1)
			+ ft_nputunbr_base_fd(p, "0123456789abcdef", 1));
	}
	return (-1000);
}

int	do_conversion(va_list args, t_prtfconv cnv)
{
	if (cnv.type == 'd' || cnv.type == 'i'
		|| cnv.type == 'x' || cnv.type == 'X' || cnv.type == 'u')
		return (do_conversion_nb(args, cnv));
	else if (cnv.type == 'c' || cnv.type == 'p' || cnv.type == 's')
		return (do_conversion_misc(args, cnv));
	else if (cnv.type == '%')
		return (ft_nputchar_fd('%', 1));
	return (-10000);
}
