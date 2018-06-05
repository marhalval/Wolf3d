/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvashchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 18:56:27 by hvashchu          #+#    #+#             */
/*   Updated: 2017/10/15 18:02:19 by hvashchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "libft/libft.h"
# include "minilibx/mlx.h"
# include <math.h>
# define WIDTH 1200
# define HEIGHT 800
# define T_WIDTH 64
# define T_HEIGHT 64

typedef	struct	s_i
{
	int			x;
	int			y;
}				t_i;

typedef	struct	s_d
{
	double		x;
	double		y;
}				t_d;

typedef struct	s_ray
{
	t_i				map;
	t_d				pos;
	t_d				dir;
	t_d				sidedist;
	t_d				delta;
	t_d				floor;
	t_d				floorcur;
	t_i				step;
	t_i				draw;
	t_i				tex;
	double			cam;
	double			dist;
	double			wall;
	int				hit;
	int				side;
	int				height;
	int				color;
}				t_ray;

typedef struct	s_me
{
	t_d			pos;
	t_d			dir;
	t_d			pln;
}				t_me;

typedef struct	s_map
{
	int			width;
	int			height;
	int			**map;
}				t_map;

typedef struct	s_wolf
{
	void		*mlx;
	void		*win;
	t_map		*map;
	t_me		*me;
	void		*img;
	char		*data;
	int			bpp;
	int			size;
	int			endi;
	int			t_w;
	int			t_h;
	int			**texture;
	int			lock;
	t_i			door;
	t_i			secretdoor;
	int			secret;
}				t_wolf;

t_map			*read_map(int fd);
t_me			*place_me(t_map *map);
void			load_texture(t_wolf *new);
void			raycast(t_wolf *new);
void			draw_wall(t_wolf *new, t_ray *ray, int x);
void			draw_floor(t_wolf *new, t_ray *ray, int x);
void			open_secret(t_wolf *new, t_me *me, t_map *map);
void			open_door(t_wolf *new, t_me *me, t_map *map);
void			go_forward(t_wolf *new, t_me *me, t_map *map, double n);
void			go_back(t_wolf *new, t_me *me, t_map *map, double n);
void			look_left(t_wolf *new, double alpha);
void			look_right(t_wolf *new, double alpha);
int				key_hook(int keycode, t_wolf *new);

#endif
