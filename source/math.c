/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 23:03:32 by pauljull          #+#    #+#             */
/*   Updated: 2019/02/20 23:33:26 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fillit.h"

int	ft_square(int nb)
{
	int sqr;
	
	sqr = 1;
	while (sqr * sqr < nb)
		sqr += 1;
	return (sqr);
}

int	power(int base, int exposant)
{
	int count;
	int result;

	count = 1;
	if (exposant == 0)
		return (1);
	result = base;
	while (count < exposant)
	{
		result *= base;
		count += 1;
	}
	return (result);
}