/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_basics.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvolikov <pvolikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 03:08:05 by pvolikov          #+#    #+#             */
/*   Updated: 2025/11/27 20:34:34 by pvolikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>
#include <libft.h>
#include <ft_printf.h>

char	**copy_map(char **map)
{
	char	**new;
	int		i;
	int		len;

	i = 0;
	while (map[i])
		i++;
	new = ft_calloc(i + 1, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		new[i] = ft_strdup(map[i]);
		if (! new[i])
			return (free_map(new), NULL);
		i++;
	}
	return (new);
}

void	print_map(char **map)
{
	int		i;

	i = 0;
	while (map[i])
	{
		ft_printf("%s\n", map[i]);
		i++;
	}
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}
