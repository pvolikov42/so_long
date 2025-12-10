#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "get_next_line.h"

char	**parse_map(char *file);
void	err(char *);

typedef struct s_coor2d
{
	int	x;
	int	y;	
}	t_coor2d;

typedef struct s_xenv
//
{
	void 	*mlx; 
	void	*win;
	void	*im[5];
	char	**map;
	char	**updmap;
	int		tilesz;
	int		persx;
	int		persy;
	int		score;
	int		stepscnt;
	int		finished;
}	t_xenv;

int		mlxrun(t_xenv *env);
void	cleanup(t_xenv *env);
int		read_images(t_xenv *e);
int		draw_map_full(t_xenv *e);
int		draw_tile(t_xenv *e, int row, int col);
int		draw_update(t_xenv *e);
int		draw_person(t_xenv *e);
void	free_map(char **map);
void	print_map(char **map);
char	**copy_map(char **map);
char	**create_updmap(char **map);
void	person_move(t_xenv *env, int dir);
void	finish_game(t_xenv *env);
int		init_person(t_xenv *env);
void	init_game(t_xenv *env);
void	game_quit(t_xenv *env);
void	err(char *s);
void	msg(char *s);
int		ft_strlen_nl(char *str);

int		check_consistency(char **map);
int		check_objects(char **map);
int		check_accessibility(char **map);

#endif

