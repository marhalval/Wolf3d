/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvashchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 19:14:30 by hvashchu          #+#    #+#             */
/*   Updated: 2017/10/11 19:14:32 by hvashchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		key_hook(int keycode, t_wolf *new)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 126)
		go_forward(new, new->me, new->map, 0.3);
	if (keycode == 125)
		go_back(new, new->me, new->map, 0.3);
	if (keycode == 124)
		look_left(new, 5.0f / 180.0f * M_PI);
	if (keycode == 123)
		look_right(new, -5.0f / 180.0f * M_PI);
	if (keycode == 49 && new->secret == 1)
	{
		new->map->map[new->secretdoor.x][new->secretdoor.y] = 5;
		new->lock = 0;
	}
	if (keycode == 49 && new->lock == 1)
	{
		new->map->map[new->door.x][new->door.y] = 0;
		new->lock = 0;
	}
	raycast(new);
	return (0);
}

void	open_door(t_wolf *new, t_me *me, t_map *map)
{
	new->lock = 1;
	if (map->map[(int)(me->pos.x) - 1][(int)(me->pos.y)] == 5)
	{
		new->door.x = (int)(me->pos.x) - 1;
		new->door.y = (int)(me->pos.y);
	}
	else if (map->map[(int)(me->pos.x) + 1][(int)(me->pos.y)] == 5)
	{
		new->door.x = (int)(me->pos.x) + 1;
		new->door.y = (int)(me->pos.y);
	}
	else if (map->map[(int)(me->pos.x)][(int)(me->pos.y) - 1] == 5)
	{
		new->door.x = (int)(me->pos.x);
		new->door.y = (int)(me->pos.y) - 1;
	}
	else if (map->map[(int)(me->pos.x)][(int)(me->pos.y) + 1] == 5)
	{
		new->door.x = (int)(me->pos.x);
		new->door.y = (int)(me->pos.y) + 1;
	}
	else
		new->lock = 0;
}

void	open_secret(t_wolf *new, t_me *me, t_map *map)
{
	new->secret = 1;
	if (map->map[(int)(me->pos.x) - 1][(int)(me->pos.y)] == 6)
	{
		new->secretdoor.x = (int)(me->pos.x) - 1;
		new->secretdoor.y = (int)(me->pos.y);
	}
	else if (map->map[(int)(me->pos.x) + 1][(int)(me->pos.y)] == 6)
	{
		new->secretdoor.x = (int)(me->pos.x) + 1;
		new->secretdoor.y = (int)(me->pos.y);
	}
	else if (map->map[(int)(me->pos.x)][(int)(me->pos.y) - 1] == 6)
	{
		new->secretdoor.x = (int)(me->pos.x);
		new->secretdoor.y = (int)(me->pos.y) - 1;
	}
	else if (map->map[(int)(me->pos.x)][(int)(me->pos.y) + 1] == 6)
	{
		new->secretdoor.x = (int)(me->pos.x);
		new->secretdoor.y = (int)(me->pos.y) + 1;
	}
	else
		new->secret = 0;
}
