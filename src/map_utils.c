#include <so_long.h>
#include <libft.h>
#include <ft_printf.h>

char	**create_updmap(char **map)
{
	char	**updmap;
	int 	i;
	int		len;

	i = 0;
	while (map[i])
		i++;
	updmap = ft_calloc(i + 1, sizeof(char *)); 
	if (!updmap)
		return (NULL);
	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		updmap[i] = (char *)malloc(sizeof(char) * (len + 1)); 
		if (! updmap[i])
			return (free_map(updmap), NULL);
		ft_memset((void *)(updmap[i]), '!', len);
		updmap[i][len] = '\0';
		i++;
	}
	return (updmap);
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
