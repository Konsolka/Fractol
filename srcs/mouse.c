/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 16:32:18 by mburl             #+#    #+#             */
/*   Updated: 2020/02/28 16:32:32 by mburl            ###   ########.fr       */
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

int		mouse_move_void(int x, int y, void *param)
{
	(void)(param);
	(void)(x);
	(void)(y);
	return (0);
}

int		mouse_release(int button, int x, int y, void *param)
{
	t_mlx	*mlx;

	if (button == MOUSE_LEFT_BUTTON)
	{
		mlx = (t_mlx *)param;
		mlx->f->k.re = 4 * ((double)x / WIDTH - 0.5);
		mlx->f->k.im = 4 * ((double)(HIEGHT - y) / HIEGHT - 0.5);
		image_put(mlx);
		mlx_hook(mlx->win, 6, 0, mouse_move_void, mlx);
	}
	return (0);
}

int		mouse_move(int x, int y, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	mlx->f->k.re = 4 * ((double)x / WIDTH - 0.5);
	mlx->f->k.im = 4 * ((double)(HIEGHT - y) / HIEGHT - 0.5);
	image_put(mlx);
	return (0);
}

int		mouse_press(int button, int x, int y, void *param)
{
	t_mlx	*mlx;
	t_compl	mouse;
	double	zoom;
	double	interpolation;

	mlx = (t_mlx *)param;
	if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
	{
		mouse = init_compl(
		(double)x / (WIDTH / (mlx->f->xmax - mlx->f->xmin)) + mlx->f->xmin,
		(double)y / (HIEGHT / (mlx->f->ymax - mlx->f->ymin)) * -1 + mlx->f->ymax
);
		zoom = (button == MOUSE_SCROLL_DOWN) ? 1.2 : 0.8;
		interpolation = 1.0 / zoom;
		mlx->f->xmin = mouse.re + ((mlx->f->xmin - mouse.re) * interpolation);
		mlx->f->ymin = mouse.im + ((mlx->f->ymin - mouse.im) * interpolation);
		mlx->f->xmax = mouse.re + ((mlx->f->xmax - mouse.re) * interpolation);
		mlx->f->ymax = mouse.im + ((mlx->f->ymax - mouse.im) * interpolation);
	}
	else if (button == MOUSE_LEFT_BUTTON)
		mlx_hook(mlx->win, 6, 0, mouse_move, mlx);
	image_put(mlx);
	return (0);
}
