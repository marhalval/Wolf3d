/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvashchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 14:44:35 by hvashchu          #+#    #+#             */
/*   Updated: 2017/10/11 14:44:37 by hvashchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	init_raycast(t_wolf *new, t_ray *ray, int x)
{
	ray->cam = 2 * x / (double)WIDTH - 1;
	ray->pos.x = new->me->pos.x;
	ray->pos.y = new->me->pos.y;
	ray->dir.x = new->me->dir.x + new->me->pln.x * ray->cam;
	ray->dir.y = new->me->dir.y + new->me->pln.y * ray->cam;
	ray->map.x = (int)ray->pos.x;
	ray->map.y = (int)ray->pos.y;
	ray->delta.x = sqrt(1 + pow(ray->dir.y, 2) / pow(ray->dir.x, 2));
	ray->delta.y = sqrt(1 + pow(ray->dir.x, 2) / pow(ray->dir.y, 2));
	ray->step.x = (ray->dir.x < 0) ? -1 : 1;
	ray->step.y = (ray->dir.y < 0) ? -1 : 1;
	ray->sidedist.x = (ray->dir.x < 0) ? (ray->pos.x - ray->map.x)
				* ray->delta.x : (ray->map.x + 1 - ray->pos.x) * ray->delta.x;
	ray->sidedist.y = (ray->dir.y < 0) ? (ray->pos.y - ray->map.y)
				* ray->delta.y : (ray->map.y + 1 - ray->pos.y) * ray->delta.y;
	ray->hit = 0;
}

static void	perform_dda(t_wolf *new, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->sidedist.x < ray->sidedist.y)
		{
			ray->sidedist.x += ray->delta.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist.y += ray->delta.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		if (new->map->map[ray->map.x][ray->map.y] > 0)
			ray->hit = 1;
	}
}

static void	calc_wall(t_wolf *new, t_ray *ray)
{
	if (ray->side == 0)
		ray->dist = (ray->map.x - ray->pos.x
		+ (1 - ray->step.x) / 2) / ray->dir.x;
	else
		ray->dist = (ray->map.y - ray->pos.y
		+ (1 - ray->step.y) / 2) / ray->dir.y;
	ray->height = (int)(HEIGHT / ray->dist);
	ray->draw.x = (HEIGHT - ray->height) / 2;
	ray->draw.x = (ray->draw.x > 0) ? ray->draw.x : 0;
	ray->draw.y = (HEIGHT + ray->height) / 2;
	ray->draw.y = (ray->draw.y >= HEIGHT) ? HEIGHT - 1 : ray->draw.y;
	ray->wall = ray->side ? ray->pos.x + ray->dist * ray->dir.x
						: ray->pos.y + ray->dist * ray->dir.y;
	ray->wall -= floor(ray->wall);
	ray->tex.x = (int)(ray->wall * (double)(T_WIDTH));
	if (ray->side == 0 && ray->dir.x > 0)
		ray->tex.x = T_WIDTH - ray->tex.x - 1;
	if (ray->side == 1 && ray->dir.y < 0)
		ray->tex.x = T_WIDTH - ray->tex.x - 1;
}

static void	calc_floor(t_wolf *new, t_ray *ray)
{
	if (ray->side == 0 && ray->dir.x > 0)
	{
		ray->floor.x = ray->map.x;
		ray->floor.y = ray->map.y + ray->wall;
	}
	else if (ray->side == 0 && ray->dir.x < 0)
	{
		ray->floor.x = ray->map.x + 1.0;
		ray->floor.y = ray->map.y + ray->wall;
	}
	else if (ray->side == 1 && ray->dir.y > 0)
	{
		ray->floor.x = ray->map.x + ray->wall;
		ray->floor.y = ray->map.y;
	}
	else
	{
		ray->floor.x = ray->map.x + ray->wall;
		ray->floor.y = ray->map.y + 1.0;
	}
	ray->draw.y = (ray->draw.y < 0) ? HEIGHT : ray->draw.y;
}

void		raycast(t_wolf *new)
{
	t_ray	ray;
	int		x;

	new->img = mlx_new_image(new->mlx, WIDTH, HEIGHT);
	new->data = mlx_get_data_addr(new->img, &new->bpp, &new->size, &new->endi);
	x = 0;
	while (x < WIDTH)
	{
		init_raycast(new, &ray, x);
		perform_dda(new, &ray);
		calc_wall(new, &ray);
		draw_wall(new, &ray, x);
		calc_floor(new, &ray);
		draw_floor(new, &ray, x);
		x++;
	}
	mlx_put_image_to_window(new->mlx, new->win, new->img, 0, 0);
	if (new->secret == 1)
		mlx_string_put(new->mlx, new->win,
						350, 300, 16777215, "secret door!");
	if (new->lock == 1)
		mlx_string_put(new->mlx, new->win,
						350, 300, 16777215, "press SPACE to open");
	mlx_destroy_image(new->mlx, new->img);
}
