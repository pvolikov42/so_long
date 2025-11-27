/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvolikov <pvolikov@student.42luxembourg.l  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:08:38 by pvolikov          #+#    #+#             */
/*   Updated: 2025/07/29 13:08:39 by pvolikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
//#include "libft/libft.h"

void	ft_cnt_putchar(char c, int *counter)
{
	ft_putchar_fd(c, 1);
	(*counter)++;
}

/*
static int	ft_putstr(const char *s)
{
	int len = 0;
	if (!s)
		s = "(null)";
	while (*s)
		len += write(1, s++, 1);
	return len;
}

static int	ft_putnbr(int n)
{
	char	buf[12];
	int		i = 0, len = 0;
	long	nb = n;

	if (nb < 0)
	{
		len += ft_putchar('-');
		nb = -nb;
	}
	if (nb == 0)
		return ft_putchar('0');
	while (nb)
	{
		buf[i++] = '0' + (nb % 10);
		nb /= 10;
	}
	while (i--)
		len += ft_putchar(buf[i]);
	return len;
}
*/
