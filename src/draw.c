/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvolikov <pvolikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 03:08:05 by pvolikov          #+#    #+#             */
/*   Updated: 2025/11/17 20:34:34 by pvolikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <so_long.h>
#include <mlx.h>
#include <libft.h>

int	read_images(t_xenv *e)
{
	int		size;
	int		w;
	int		h;
	int		i;
	char	*filename[5];

	size = e->tilesz;
	i = 0;
	filename[0] = "rsrc/floor_32x32.xpm";
	filename[1] = "rsrc/wall_32x32.xpm";
	filename[2] = "rsrc/person_32x32.xpm";
	filename[3] = "rsrc/coll1_32x32.xpm";
	filename[4] = "rsrc/exit_32x32.xpm";
	while (i < 5)
	{
		e->im[i] = mlx_xpm_file_to_image(e->mlx, filename[i], &w, &h);
		if (!(e->im[i]))
			return (err("Couldn't read file image from file"), 0);
		if (w != size || h != size)
			return (err("image is not 32x32\n"), 0);
		ft_printf("file %s is read\n", filename[i]);
		i++;
	}
	return (1);
}

int	draw_person(t_xenv *e)
{
	mlx_put_image_to_window(e->mlx, e->win, e->im[2],
		e->persx * e->tilesz, e->persy * e->tilesz);
	return (0);
}

int	draw_tile(t_xenv *e, int row, int col)
{
	int		size;
	void	*image;

	size = e->tilesz;
	if (e->map[row][col] == '1')
		image = e->im[1];
	else
		image = e->im[0];
	if (e->map[row][col] == 'P')
		image = e->im[2];
	if (e->map[row][col] == 'C')
		image = e->im[3];
	if (e->map[row][col] == 'E')
		image = e->im[4];
	mlx_put_image_to_window(e->mlx, e->win, image, col * size, row * size);
	return (1);
}

int	draw_map_full(t_xenv *e)
{
	int		row;
	int		col;

	row = 0;
	while (e->map[row])
	{
		col = -1;
		while (e->map[row][++col])
			draw_tile(e, row, col);
		row++;
	}
	return (0);
}

int	draw_update(t_xenv *e)
{
	int		i;
	int		j;

	i = 0;
	while (e->updmap[i])
	{
		j = 0;
		while (e->updmap[i][j])
		{
			if (e->updmap[i][j] == '!')
			{
				draw_tile(e, i, j);
				e->updmap[i][j] = '.';
			}
			j++;
		}
		i++;
	}
	return (0);
}
