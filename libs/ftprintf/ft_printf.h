/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvolikov <pvolikov@student.42luxembourg.l  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:11:09 by pvolikov          #+#    #+#             */
/*   Updated: 2025/07/30 03:03:12 by pvolikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

typedef struct s_prtfconv
{
	char	type;
}	t_prtfconv;

void	ft_cnt_putchar(char c, int *counter);
int		do_conversion(va_list arg, t_prtfconv cnv);
int		ft_printf(const char *format, ...);

#endif
