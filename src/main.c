#include <libft.h>
#include <so_long.h>
#include <ft_printf.h>

int	main(int argc, char **argv)
{
	char	**map;
	char	**updmap;
	t_xenv	env;
	int		lines;

	if (argc != 2)
		return (ft_putstr_fd("Usage: ./so_long map.ber\n", 2), 1);
	map = parse_map(argv[1]);
	if (!map)
		return (err("Error loading map\n"), 2);
	print_map(map);
	ft_printf("---\n");
	lines = 0;
	while (map[lines])
		lines++;
	ft_printf("Map is: %d x %d\n----\n", lines ,ft_strlen(map[0]));
	updmap = create_updmap(map);
	if (!updmap)
		return (err("Error allocating update map\n"), 3);
	print_map(updmap);
	ft_printf("---\n");
	env.map = map;
	env.updmap = updmap;
	mlxtry(&env);
	// free map after use
	free_map(map);
	free_map(updmap);
}
//https://github.com/crawl/tiles
