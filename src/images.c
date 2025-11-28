/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
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

void	cleanup(t_xenv *env)
{
	int	i;

	i = 0;
	while (i < 5)
		if (env->im[i])
			mlx_destroy_image(env->mlx, env->im[i++]);
}
