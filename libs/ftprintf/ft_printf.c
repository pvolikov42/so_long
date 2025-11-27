/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvolikov <pvolikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:19:11 by pvolikov          #+#    #+#             */
/*   Updated: 2025/07/22 20:14:08 by pvolikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
//#include <stdio.h>
#include "ft_printf.h"
//#include "libft/libft.h"
#include <libft.h>

int	is_correct_conv_spec(const char *fmtstr, t_prtfconv *converter, int *cnt)
{
	const char	conversions[] = "cdispuxX%";
	char		*pos;

	(void)converter;
	pos = ft_strchr(conversions, fmtstr[0]);
	if (pos)
	{
		converter->type = fmtstr[0];
		*cnt += 1;
		return (1);
	}
	converter->type = '\0';
	return (0);
}

int	ft_printf(const char *format, ...)
// Look for a '%' then read conversion flags 
// until the first nonflag character found
// then passes to the conversion
{
	va_list		args;
	int			i;
	int			count;
	t_prtfconv	converter;

	va_start(args, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			if (is_correct_conv_spec(format + i + 1, &converter, &i))
				count += do_conversion(args, converter);
			else
				ft_cnt_putchar(format[i], &count);
		}
		else
			ft_cnt_putchar(format[i], &count);
		i++;
	}
	va_end(args);
	return (count);
}
