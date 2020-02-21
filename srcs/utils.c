/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 17:26:28 by mburl             #+#    #+#             */
/*   Updated: 2020/02/21 18:32:56 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cl_h.h"
#include <mlx.h>
#include "window.h"
#include "keys.h"
#include "visual.h"

void		draw_square(t_point coords, t_point size, t_mlx *mlx, int color)
{
	int		i;
	int		j;
	int		temp;

	i = coords.x;
	while (i < size.x + coords.x)
	{
		j = coords.y;
		while (j < size.y + coords.y)
		{
			temp = (i * mlx->bpp / 8) + (j * mlx->line_size);
			mlx->line[temp] = color;
			mlx->line[temp] = color >> 8;
			mlx->line[temp] = color >> 16;
			j++;
		}
		i++;
	}
}

t_compl	init_compl(const double re, const double im)
{
	t_compl	ret;

	ret.re = re;
	ret.im = im;
	return (ret);
}

void	draw_menu_strings(t_mlx *mlx)
{
	mlx_string_put(mlx->ptr, mlx->win, 20, 20 + 20, COLOR_WHITE, "--Arrow up--");
	mlx_string_put(mlx->ptr, mlx->win, 20, 20 + 45, COLOR_WHITE, "Increase itertations");
	mlx_string_put(mlx->ptr, mlx->win, 20, 20 + 70, COLOR_WHITE, "--Arrow down--");
	mlx_string_put(mlx->ptr, mlx->win, 20, 20 + 95, COLOR_WHITE, "Decrease itertations");
	mlx_string_put(mlx->ptr, mlx->win, 20, 20 + 120, COLOR_WHITE, "--Mouse scroll up--");
	mlx_string_put(mlx->ptr, mlx->win, 20, 20 + 145, COLOR_WHITE, "Zoom in");
	mlx_string_put(mlx->ptr, mlx->win, 20, 20 + 170, COLOR_WHITE, "--Mouse scroll down--");
	mlx_string_put(mlx->ptr, mlx->win, 20, 20 + 195, COLOR_WHITE, "Zoom out");
	mlx_string_put(mlx->ptr, mlx->win, 20, 20 + 220, COLOR_WHITE, "--R--        --ESC--");
	mlx_string_put(mlx->ptr, mlx->win, 20, 20 + 245, COLOR_WHITE, "Reset         Exit");

}
void	draw_menu(t_mlx *mlx)
{
	t_point		point;
	t_point		size;

	point.x = 0;
	point.y = 0;
	size.x = 250;
	size.y = 310;
	draw_square(point, size, mlx, COLOR_WHITE);
	point.x = 5;
	point.y = 5;
	size.x -= point.x * 2;
	size.y -= point.y * 2;
	draw_square(point, size, mlx, 0x222222);
}