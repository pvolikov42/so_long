#include <mlx.h>
#include <unistd.h>
#include <libft.h>
#include <ft_printf.h>
#include <stdio.h>
#include <stdlib.h>
#include <so_long.h>
#include <sys/time.h>

void	err(char *s)
{
	char	*msg;

	msg = ft_strjoin("ERR: ", s);
	write(2, msg, ft_strlen(msg));
	free(msg);
}

void	msg(char *s)
{
	write(1, s, ft_strlen(s));
}

void	cleanup(t_xenv *env)
{
	int i;

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
//	ft_printf("I1: Key pressed : %x\n", key);
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

int loop_test(void *p)
{
	if (p) p = p;
	ft_printf("looping...\n");
	return (0);
}

int	loop_win1(void *p)
{
	static long	last;
	long	now;
	t_xenv	*e;
	struct timeval	t;

	e = (t_xenv *)p;
	gettimeofday(&t, NULL);
	now = t.tv_sec * 1000 + t.tv_usec / 1000;
//	now = last + 30;
	if (now - last >= 15)
	{
//		printf("msecs = %ld: time to update... \n", last);
//		fflush(stdout);
		draw_update(e);
		last = now;
		if (e->finished)
			game_quit(e);
//		usleep(10000);
	}
	usleep(10000);
	return (0);
}

int mlxtry(t_xenv *xenv)
{
	void    *mlx;
	void    *win;

//	xenv = (t_xenv *)malloc(sizeof(t_xenv));
//	if (!xenv)
//		return (99);
	
	// Initialize MiniLibX
	mlx = mlx_init();
	if (!mlx)
	{
		err("Didn't connect to X server\n");
		return (0);
	}
	xenv->mlx = mlx;
	// Create a new window (width: 800, height: 600)
	win = mlx_new_window(mlx, 800, 600, "Kracken loves sushi");
	if (!win)
		return (0);
	xenv->win = win;
	xenv->tilesz = 32;
	sleep(1);
	if (! read_images(xenv)) 
		return(0);
	ft_printf("traceA\n");
//	draw_map_full(xenv);
//	draw_update(xenv);
//	draw_tile(xenv, 0, 0);
	xenv->persx = 1;
	xenv->persy = 1;
	draw_person(xenv);
	init_game(xenv);
	ft_printf("traceB\n");
	// Start the event loop (keeps the window open)
	mlx_key_hook(win, key_win1, (void *)xenv);
	mlx_loop_hook(mlx, loop_win1, (void *)xenv);
//	mlx_loop_hook(mlx, loop_test, (void *)xenv);
	ft_printf("traceC\n");
	mlx_loop(mlx);
	ft_printf("End of loop! \n");
	cleanup(xenv);
	mlx_destroy_display(mlx);
	free(mlx);
	return (1);
}

