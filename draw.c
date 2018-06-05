/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvashchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 17:37:03 by hvashchu          #+#    #+#             */
/*   Updated: 2017/10/15 17:37:05 by hvashchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	draw_pixel(t_wolf *new, int x, int y, int color)
{
	new->data[y * new->size + x * 4] = (color % 256);
	new->data[y * new->size + x * 4 + 1] = (color % 65536 / 256);
	new->data[y * new->size + x * 4 + 2] = (color / 65536);
}

void		draw_wall(t_wolf *new, t_ray *ray, int x)
{
	int		y;
	int		dist;
	int		texnum;

	texnum = new->map->map[ray->map.x][ray->map.y] - 1;
	y = ray->draw.x;
	while (y < ray->draw.y)
	{
		dist = y * 256 - HEIGHT * 128 + ray->height * 128;
		ray->tex.y = ((dist * T_HEIGHT) / ray->height) / 256;
		ray->color = new->texture[texnum][T_WIDTH * ray->tex.y + ray->tex.x];
		if (ray->side == 1)
			ray->color = (ray->color >> 1) & 8355711;
		draw_pixel(new, x, y, ray->color);
		y++;
	}
}

void		draw_floor(t_wolf *new, t_ray *ray, int x)
{
	int		y;
	double	distwall;
	double	distplr;
	double	distcur;
	double	weight;

	distplr = 0.0;
	distwall = ray->dist;
	y = ray->draw.y + 1;
	while (y < HEIGHT)
	{
		distcur = HEIGHT / (2.0 * y - HEIGHT);
		weight = (distcur - distplr) / (distwall - distplr);
		ray->floorcur.x = weight * ray->floor.x + (1.0 - weight) * ray->pos.x;
		ray->floorcur.y = weight * ray->floor.y + (1.0 - weight) * ray->pos.y;
		ray->tex.x = (int)(ray->floorcur.x * T_WIDTH) % T_WIDTH;
		ray->tex.y = (int)(ray->floorcur.y * T_HEIGHT) % T_HEIGHT;
		ray->color = new->texture[8][T_WIDTH * ray->tex.y + ray->tex.x];
		draw_pixel(new, x, y, ray->color);
		ray->color = new->texture[9][T_WIDTH * ray->tex.y + ray->tex.x];
		draw_pixel(new, x, HEIGHT - y, ray->color);
		y++;
	}
}
