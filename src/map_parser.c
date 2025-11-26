#include "so_long.h"
#include <libft.h>

static int	ft_strlen_nl(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

/*
static char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	joined = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!joined)
		return (NULL);
	i = -1;
	while (s1[++i])
		joined[i] = s1[i];
	j = 0;
	while (s2[j])
		joined[i++] = s2[j++];
	joined[i] = '\0';
	free(s1);
	return (joined);
}
*/

static void	replace_nl_with_zero(unsigned int i, char *s)
{
	i = 0;
	if (s[i] == '\n')
		s[i] ='\0';
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

static int	check_rectangular(char **map)
{
	int	len;
	int	i;

	len = ft_strlen_nl(map[0]);
	i = 0;
	while (map[i])
	{
		if (ft_strlen_nl(map[i]) != len)
			return (0);
		i++;
	}
	return (1);
}

char	**parse_map(char *file)
{
	int		fd;
	int		lines;
	char	**map;
	int		i;

	if (!file || ft_strnstr(file, ".ber", ft_strlen(file)) == NULL)
		return (NULL);
	lines = count_lines(file);
	if (lines == 0)
		return (NULL);
	if (lines > 600 / 32)
			return ( err("Map has too many rows\n"), NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = malloc(sizeof(char *) * (lines + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i < lines)
	{
		map[i] = get_next_line(fd);
		ft_striteri(map[i], &replace_nl_with_zero);
		i++;
	}
	map[i] = NULL;
	close(fd);
	if (ft_strlen(map[0]) > 800 / 32) 
		return (err("Map has too many rows\n"), NULL);
	if (!check_rectangular(map))
	{
		err("Error: Map is not rectangular\n");
		return (NULL);
	}
	return (map);
}

