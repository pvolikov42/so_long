/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvolikov <pvolikov@student.42luxembourg.l  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:30:17 by pvolikov          #+#    #+#             */
/*   Updated: 2025/07/29 13:41:01 by pvolikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include "ft_printf.h"

void	test_simple(void)
{
	int		count;
	int		n;

	count = ft_printf("No format specifiers here.\n");
	printf("Printed %d characters.\n", count);
	n = 5;
	count = ft_printf("Hello %s! You have %d new message(s).\n", "Alice", n);
	printf("Printed %d characters.\n", count);
	count = ft_printf("Character: %c, Number: %d\n", 'A', INT_MIN);
	printf("Printed %d characters.\n", count);
	n = -163;
	count = ft_printf("Pointer: %p, int: %d, unsigned: %u\n", &n, n, n);
	printf("Printed %d characters.\n", count);
	count = ft_printf("hex: %x, HEX: %X\n", n, n);
	printf("Printed %d characters.\n", count);
}

int	main(void)
{
	int		count;
	int		countft;
	char	*s;
	char	*ss;

	s = "test string";
	test_simple();
	printf("   printf:");
	count = printf("%s", s);
	printf("\n");
	printf("ft_printf:");
	fflush(stdout);
	countft = ft_printf("%s", s);
	printf("\n%d =?= %d\n", count, countft);
	fflush(stdout);
	printf("original hex: %x\n", -163);
	printf("original ptr: %p\n", &count);
	ss = (char *) NULL;
	printf("original with str null: %s\n", ss);
	printf("original ptr to NULL: %p\n", NULL);
	return (0);
}
