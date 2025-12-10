/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvolikov <pvolikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 03:08:05 by pvolikov          #+#    #+#             */
/*   Updated: 2025/12/09 20:34:34 by pvolikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <libft.h>
#include <ft_printf.h>

int	is_wall(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_accessibility(char **map)
{
	if (map)
		return (1);
	return (1);
}

/*int	check_accessibility(char **map)
{
	t_pos	pp;

	pp = find_person(map);
	map2 = copy_map(map);
	fill_map_by_value(map2, 0, 8, pp);
	check_contact(map2);
	free_map(map2);
}
*/

int	check_objects(char **map)
{
	int	i;
	int	j;
	int	pcnt;
	int	ecnt;

	pcnt = 0;
	ecnt = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			pcnt += (map[i][j] == 'P');
			ecnt += (map[i][j] == 'E');
			j++;
		}
		i++;
	}
	if (pcnt > 1)
		return (err("Bad map: too much players\n"), 0);
	if (ecnt > 1)
		return (err("Bad map: too much exits\n"), 0);
	return (1);
}

int	check_consistency(char **map)
{
	int	i;
	int	w;
	int	h;

	w = ft_strlen_nl(map[0]);
	h = 0;
	while (map[h])
		h++;
	ft_printf("w=%d h=%d\n", w, h);
	if (! (is_wall(map[0]) && is_wall(map[h - 1])))
		return (err("Map walls are broken\n"), 0);
	i = 1;
	while (i < h - 1)
	{
		if (map[i][0] == '1' && map[i][w - 1] == '1')
			i++;
		else
			return (err("Map walls are broken\n"), 0);
	}
	if (! (check_objects(map) && check_accessibility(map)))
		return (err("Map has logic errors\n"), 0);
	return (1);
}
