int	main(int argc, char **argv)
{
	char	**map;
	int		i;

	if (argc != 2)
		return (ft_putstr_fd("Usage: ./so_long map.ber\n", 2), 1);
	map = parse_map(argv[1]);
	if (!map)
		return (ft_putstr_fd("Error loading map\n", 2), 1);
	i = 0;
	while (map[i])
		ft_printf("%s", map[i++]); // Or printf if allowed
	// free map after use
	return (0);
}

