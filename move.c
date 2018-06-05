/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvashchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 16:38:30 by hvashchu          #+#    #+#             */
/*   Updated: 2017/10/15 16:38:32 by hvashchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	go_forward(t_wolf *new, t_me *me, t_map *map, double n)
{
	if (map->map[(int)(me->pos.x + me->dir.x * n)][(int)(me->pos.y)] == 0)
		me->pos.x += me->dir.x * n;
	if (map->map[(int)(me->pos.x)][(int)(me->pos.y + me->dir.y * n)] == 0)
		me->pos.y += me->dir.y * n;
	open_secret(new, me, map);
	open_door(new, me, map);
}

void	go_back(t_wolf *new, t_me *me, t_map *map, double n)
{
	new->secret = 0;
	new->lock = 0;
	if (map->map[(int)(me->pos.x - me->dir.x * n)][(int)(me->pos.y)] == 0)
		me->pos.x -= me->dir.x * n;
	if (map->map[(int)(me->pos.x)][(int)(me->pos.y - me->dir.y * n)] == 0)
		me->pos.y -= me->dir.y * n;
}

void	look_left(t_wolf *new, double alpha)
{
	double	dir_tmp;
	double	pos_tmp;

	dir_tmp = new->me->dir.x;
	new->me->dir.x = new->me->dir.x * cos(alpha) - new->me->dir.y * sin(alpha);
	new->me->dir.y = dir_tmp * sin(alpha) + new->me->dir.y * cos(alpha);
	pos_tmp = new->me->pln.x;
	new->me->pln.x = new->me->pln.x * cos(alpha) - new->me->pln.y * sin(alpha);
	new->me->pln.y = pos_tmp * sin(alpha) + new->me->pln.y * cos(alpha);
}

void	look_right(t_wolf *new, double alpha)
{
	double	dir_tmp;
	double	pos_tmp;

	dir_tmp = new->me->dir.x;
	new->me->dir.x = new->me->dir.x * cos(alpha) - new->me->dir.y * sin(alpha);
	new->me->dir.y = dir_tmp * sin(alpha) + new->me->dir.y * cos(alpha);
	pos_tmp = new->me->pln.x;
	new->me->pln.x = new->me->pln.x * cos(alpha) - new->me->pln.y * sin(alpha);
	new->me->pln.y = pos_tmp * sin(alpha) + new->me->pln.y * cos(alpha);
}
