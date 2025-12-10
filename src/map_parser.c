/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvolikov <pvolikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 03:08:05 by pvolikov          #+#    #+#             */
/*   Updated: 2025/11/27 20:34:34 by pvolikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <libft.h>

static void	replace_nl_with_zero(unsigned int i, char *s)
{
	i = 0;
	if (s[i] == '\n')
		s[i] = '\0';
}

static int	count_lines(char *file)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

static int	check_geometry(char **map)
{
	int	len;
	int	i;

	len = ft_strlen_nl(map[0]);
	i = 0;
	while (map[i])
	{
		if (ft_strlen_nl(map[i]) != len)
			return (err("Error: Map is not rectangular\n"), 0);
		i++;
	}
	if (i > 600 / 32)
		return (err("Map has too many rows\n"), 0);
	if (ft_strlen(map[0]) > 800 / 32)
		return (err("Map has too many columns\n"), 0);
	return (1);
}

static void	read_nlines_into_map(int fd, char **map, int lines)
{
	int	i;

	i = 0;
	while (i < lines)
	{
		map[i] = get_next_line(fd);
		ft_striteri(map[i], &replace_nl_with_zero);
		i++;
	}
	map[i] = NULL;
}

char	**parse_map(char *file)
{
	int		fd;
	int		lines;
	char	**map;

	if (!file || ft_strnstr(file, ".ber", ft_strlen(file)) == NULL)
		return (NULL);
	lines = count_lines(file);
	if (lines == 0)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = malloc(sizeof(char *) * (lines + 1));
	if (!map)
		return (NULL);
	read_nlines_into_map(fd, map, lines);
	close(fd);
	if (!check_geometry(map))
		return (NULL);
	if (!check_consistency(map))
		return (NULL);
	return (map);
}
