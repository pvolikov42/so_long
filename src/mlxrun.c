/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxrun.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvolikov <pvolikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 03:08:05 by pvolikov          #+#    #+#             */
/*   Updated: 2025/11/27 20:34:34 by pvolikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <unistd.h>
#include <libft.h>
#include <ft_printf.h>
#include <stdlib.h>
#include <so_long.h>
#include <sys/time.h>

void	cleanup(t_xenv *env)
{
	int	i;

	i = 0;
	while (i < 5)
		if (env->im[i])
			mlx_destroy_image(env->mlx, env->im[i++]);
}

void	game_quit(t_xenv *env)
{
	ft_printf("closing window... \n");
	mlx_destroy_window(env->mlx, env->win);
	mlx_loop_end(env->mlx);
}

int	key_win1(int key, void *p)
{
	t_xenv	*e;

	e = (t_xenv *)p;
	if (key == 0xFF1B)
	{
		ft_printf("Esc key pressed, bailing out... \n");
		e->finished = 1;
	}
	if (key == 0xFF51)
		person_move(e, 1);
	if (key == 0xFF52)
		person_move(e, 2);
	if (key == 0xFF53)
		person_move(e, 3);
	if (key == 0xFF54)
		person_move(e, 4);
	ft_printf("Steps: %d, score: %d\n", e->stepscnt, e->score);
	return (0);
}

int	loop_win1(void *p)
{
	static long		last;
	long			now;
	t_xenv			*e;
	struct timeval	t;

	e = (t_xenv *)p;
	gettimeofday(&t, NULL);
	now = t.tv_sec * 1000 + t.tv_usec / 1000;
	if (now - last >= 15)
	{
		draw_update(e);
		last = now;
		if (e->finished)
			game_quit(e);
	}
	usleep(10000);
	return (0);
}

int	mlxrun(t_xenv *xenv)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	if (!mlx)
		return (err("Didn't connect to X server\n"), 0);
	xenv->mlx = mlx;
	win = mlx_new_window(mlx, 800, 600, "Kracken loves sushi");
	if (!win)
		return (0);
	xenv->win = win;
	xenv->tilesz = 32;
	sleep(1);
	if (! read_images(xenv))
		return (0);
	init_game(xenv);
	mlx_key_hook(win, key_win1, (void *)xenv);
	mlx_loop_hook(mlx, loop_win1, (void *)xenv);
	mlx_loop(mlx);
	ft_printf("End of loop! \n");
	cleanup(xenv);
	mlx_destroy_display(mlx);
	free(mlx);
	return (1);
}
