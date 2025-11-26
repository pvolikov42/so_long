/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvolikov <pvolikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 03:08:05 by pvolikov          #+#    #+#             */
/*   Updated: 2025/11/17 20:34:34 by pvolikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>
#include <ft_printf.h>

void	init_game(t_xenv *e)
{
	e->finished = 0;
	e->score = 0;
	e->stepscnt = 0;
	init_person(e);
}

int	init_person(t_xenv *e)
{
	int	i;
	int	j;

	e->persx = 0;
	e->persy = 0;
	i = 0;
	while (e->map[i])
	{
		j = 0;
		while (e->map[i][j])
		{
			if (e->map[i][j] == 'P')
				return (e->persx = j, e->persy = i, 1);
			j++;
		}
		i++;
	}
	return (0);
}

static void	dir_helper(int dir, t_coor2d *pos, t_coor2d *npos)
{
	if (dir == 1)
		npos->x = pos->x - 1;
	if (dir == 2)
		npos->y = pos->y - 1;
	if (dir == 3)
		npos->x = pos->x + 1;
	if (dir == 4)
		npos->y = pos->y + 1;
}

void	person_move(t_xenv *e, int dir)
{
	t_coor2d	pos;
	t_coor2d	npos;

	pos.y = e->persy;
	pos.x = e->persx;
	npos.y = pos.y;
	npos.x = pos.x;
	dir_helper(dir, &pos, &npos);
	if (e->map[npos.y][npos.x] == 'E')
		finish_game(e);
	if (e->map[npos.y][npos.x] == 'C')
		e->score++;
	if (e->map[npos.y][npos.x] != '1')
	{
		e->map[npos.y][npos.x] = 'P';
		e->map[pos.y][pos.x] = '0';
		e->updmap[pos.y][pos.x] = '!';
		e->updmap[npos.y][npos.x] = '!';
		e->persy = npos.y;
		e->persx = npos.x;
		e->stepscnt++;
	}
}

void	finish_game(t_xenv *e)
{
	ft_printf("It was so long indeed!\n");
	ft_printf("%d steps done\n", e->stepscnt);
	ft_printf("%d item(s) collected\n", e->score);
	e->finished = 1;
}
