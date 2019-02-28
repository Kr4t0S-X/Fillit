/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 14:16:53 by pauljull          #+#    #+#             */
/*   Updated: 2019/02/28 19:23:01 by cghanime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#include "../include/fillit.h"

t_map	*reset_map(t_tetri *tetri, t_map *map)
{
	char i;
	t_map *save;

	save = map;
	i = 1;
	while (map->index != tetri->pos_y)
		map = map->next;
	while (i <= tetri->length)
	{
		map->line ^= (set_fblock_bit(tetri->tetri, i, tetri->decal) >> (i - 1) * 4);
		map = map->next;
		i += 1;
	}
	return (save);
}

void	solver_iteratif(t_tetri **tetri_ref, t_map **map_ref)
{
	t_tetri	*l_tetri;
	t_map	*l_map;
	t_tetri *save;
	int		decal;

	l_tetri = *tetri_ref;
	l_map = *map_ref;
	decal = 0;
	while (l_tetri)
	{
		while (l_map->next && l_tetri)
		{
			if (multi_check(l_tetri, l_map))
			{
				set_tetri_map(&l_tetri, &l_map);
				l_tetri = l_tetri->next;
				l_map = *map_ref;
				decal = 0;
			}
			else if (l_tetri->pos_x << (1 + l_tetri->width) <= power(2, l_map->width))
			{	
				l_tetri->tetri <<= 1;
				l_tetri->pos_x <<= 1;
				decal += 1;
			}
			else if (l_map->next && l_tetri->length <= (l_map->width - l_map->next->index))
			{
				l_map = l_map->next;
				l_tetri->tetri >>= decal;
				l_tetri->pos_y += 1;
				l_tetri->pos_x = 1;
				decal = 0;
			}
		}
		if (l_tetri)
			l_tetri = l_tetri->next;
	}
}

void solver_recursif(t_tetri *tetri, t_map *map, int val)
{
	printf("%d\n", val++);
	if (multi_check(tetri, map))
	{
		printf(KRED "ca passe multi check ok\n");
		set_tetri_map(&tetri, &map);
		if (tetri->next)
			solver_recursif(tetri->next, map->head, val);
	}
	else if (tetri->pos_x << (1 + tetri->width) <= power(2, map->width))
	{
		printf(KBLU "ca passe else if 1\n");
		tetri->tetri <<= 1;
		tetri->pos_x <<= 1;
		tetri->decal += 1;
		solver_recursif(tetri, map, val);
	}
	else if (map->next && tetri->length <= (map->width - map->next->index))
	{
		printf(KGRN "ca passe else if 2\n");
		map = map->next;
		tetri->tetri >>= tetri->decal;
		tetri->pos_y += 1;
		tetri->pos_x = 1;
		tetri->decal = 0;
		solver_recursif(tetri, map, val);
	}
	else if (!tetri->prev)
	{
		printf(KCYN "ca passe else if 3 map = map->width + 1\n");
		while (map->next)
		{
			map->line = 0;
			map = map->next;
		}
		map->line = 0;
		printf(KCYN "map->index = %d\n", map->index);
		map = ft_lpb_map(&map, map->width + 1, map->index + 1);
		printf(KCYN "map->index = %d\n", map->index);
		solver_recursif(tetri, map, val);
	}
	else
	{
		printf(KMAG "ca passe else final backtracking\n");
		map = reset_map(tetri->prev, map->head);
		tetri->prev->tetri <<= 1;
		tetri->prev->decal += 1;
		solver_recursif(tetri->prev, map, val);
	}
}