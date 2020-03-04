/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 17:26:28 by mburl             #+#    #+#             */
/*   Updated: 2020/03/04 16:17:03 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cl_h.h"
#include <mlx.h>
#include "window.h"
#include "keys.h"
#include "visual.h"
#include "libft.h"

t_compl		init_compl(const double re, const double im)
{
	t_compl	ret;

	ret.re = re;
	ret.im = im;
	return (ret);
}

void		change_pos(t_fractol *f, int key)
{
	if (key == KEY_A)
	{
		f->xmin += 10 * f->factor.re;
		f->xmax += 10 * f->factor.re;
	}
	else if (key == KEY_S)
	{
		f->ymax += 10 * f->factor.im;
		f->ymin += 10 * f->factor.im;
	}
	else if (key == KEY_D)
	{
		f->xmin -= 10 * f->factor.re;
		f->xmax -= 10 * f->factor.re;
	}
	else if (key == KEY_W)
	{
		f->ymax -= 10 * f->factor.im;
		f->ymin -= 10 * f->factor.im;
	}
}

void		draw_menu(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
mlx_string_put(mlx->ptr, mlx->win, 460, 325,
		COLOR_AL_GRAY, "Controls");
	mlx_string_put(mlx->ptr, mlx->win, 385, 370,
		COLOR_AL_GRAY, "Hide menu     - H");
	mlx_string_put(mlx->ptr, mlx->win, 385, 400,
		COLOR_AL_GRAY, "Itertations   - Arrow up / down");
	mlx_string_put(mlx->ptr, mlx->win, 385, 430,
		COLOR_AL_GRAY, "Zoom          - Scroll");
	mlx_string_put(mlx->ptr, mlx->win, 385, 460,
		COLOR_AL_GRAY, "WASD          - Movement");
	mlx_string_put(mlx->ptr, mlx->win, 385, 490,
		COLOR_AL_GRAY, "Color         - 1..6 / B");
	mlx_string_put(mlx->ptr, mlx->win, 385, 520,
		COLOR_AL_GRAY, "Fractals      - P / N");
	mlx_string_put(mlx->ptr, mlx->win, 385, 550,
		COLOR_AL_GRAY, "Reset         - R");
	mlx_string_put(mlx->ptr, mlx->win, 385, 580,
		COLOR_AL_GRAY, "Exit          - ESC");
}

void		error_put(void)
{
	ft_putstr_err("Usage:\n");
	ft_putstr_err("\t./fractol [set]\n");
	ft_putstr_err("Sets:\n");
	ft_putstr_err("\t1: Mandelbrot\n");
	ft_putstr_err("\t2: Julia\n\t3: Burning Ship\n");
	exit(-1);
}
