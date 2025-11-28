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
#include <mlx_int.h>
#include <unistd.h>
#include <libft.h>
#include <ft_printf.h>
#include <stdlib.h>
#include <so_long.h>
#include <sys/time.h>

void	game_quit(t_xenv *env)
{
	ft_printf("closing window... \n");
	mlx_destroy_window(env->mlx, env->win);
	mlx_loop_end(env->mlx);
}

int	key_win(int key, void *p)
{
	t_xenv	*e;

	e = (t_xenv *)p;
	if (key == 0xFF1B)
	{
		ft_printf("Esc key pressed, bailing out... \n");
		e->finished = 1;
	}
	if (key == 0xFF51 || key == 0x61)
		person_move(e, 1);
	if (key == 0xFF52 || key == 0x77)
		person_move(e, 2);
	if (key == 0xFF53 || key == 0x64)
		person_move(e, 3);
	if (key == 0xFF54 || key == 0x73)
		person_move(e, 4);
	ft_printf("Steps: %d, score: %d\n", e->stepscnt, e->score);
	return (1);
}

int	quit_win_req(void *p)
{
	t_xenv	*e;

	e = (t_xenv *)p;
	e->finished = 1;
	return (1);
}
/*
int	event_check(void *p)
{
	int	n;

	n = *(int *)p;
	ft_printf("Event happened in window. %d\n", n);
	return (1);
}*/

int	loop_proc(void *p)
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
	return (1);
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
	mlx_key_hook(win, key_win, (void *)xenv);
	mlx_hook(win, DestroyNotify, 1L << 17, quit_win_req, (void *)xenv);
	mlx_loop_hook(mlx, loop_proc, (void *)xenv);
	mlx_loop(mlx);
	ft_printf("End of loop! \n");
	cleanup(xenv);
	mlx_destroy_display(mlx);
	free(mlx);
	return (1);
}
