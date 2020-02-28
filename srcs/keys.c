/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 13:15:00 by mburl             #+#    #+#             */
/*   Updated: 2020/02/28 16:33:24 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <unistd.h>
#include "cl_h.h"
#include "visual.h"
#include "libft.h"
#include "keys.h"
#include "window.h"

void	change_fractal(t_mlx *mlx, int key)
{
	mlx->change = 1;
	mlx->set += (key == 35) ? 1 : -1;
	mlx->set = (mlx->set > 3) ? 1 : mlx->set;
	mlx->set = (mlx->set < 1) ? 3 : mlx->set;
	re_draw(mlx->set, mlx);
}

int		key_parce(int key, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (key == MAIN_PAD_ESC)
		win_close(mlx);
	else if (key == ARROW_UP)
		mlx->f->iter += (mlx->f->iter + 1 > 10) ? 10 : 1;
	else if (key == ARROW_DOWN && mlx->f->iter > 2)
		mlx->f->iter -= (mlx->f->iter - 10 < 10) ? 1 : 10;
	else if (key == 15)
		fractol_init(mlx->f);
	else if (key == 4)
		mlx->menu = (mlx->menu == 1) ? 0 : 1;
	else if (18 <= key && key <= 23)
		mlx->f->color = key - 17;
	else if (key == 35 || key == 45)
	{
		change_fractal(mlx, key);
		return (0);
	}
	else if (key == KEY_B)
		mlx->f->s = (mlx->f->s == 1) ? 0 : 1;
	image_put(mlx);
	return (0);
}
