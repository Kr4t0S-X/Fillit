#include "../include/fillit.h"

void	print_tetri(t_tetri *tetri)
{
	print_tetri_bit(tetri->tetri);
	printf("\nletter : %c\n", tetri->letter);
	printf("length : %d\n", tetri->length);
	printf("width : %d\n", tetri->width);
	printf("pos_x : %d\n\n", tetri->pos_x);
	printf("pos_y : %d\n###############################\n\n", tetri->pos_y);
}

void	print_map_bit(t_map *map)
{
	int mask;
	int i;

	mask = 1;
	i = 0;
	while (map->next)
	{
		while (i < map->width)
		{
			if ((map->line & mask) != 0)
				write(1, "1", 1);
			else
				write(1, "0", 1);
			i += 1;
			mask <<= 1;
		}
		write(1, "\n", 1);
		i = 0;
		mask = 1;
		map = map->next;
	}
}

void	print_tetri_bit(int tetri)
{
	int mask;
	int count;

	count = 0;
	mask = 1;
	while (mask < 65536)
	{
		if ((tetri & mask) != 0)
			write(1, "1", 1);
		else
			write(1, "0", 1);
		mask <<= 1;
		count += 1;
		if (count == 4)
		{
			write(1, "\n", 1);
			count = 0;
		}
	}
}

void	print_bit_int(int wallah)
{
	unsigned int mask;

	mask = 1;
	while (mask < 2147483648)
	{
		if (mask & wallah)
			write(1, "1", 1);
		else
			write (1,"0", 1);
		mask <<= 1;	
	}
}