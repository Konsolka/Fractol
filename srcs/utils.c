/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 17:26:28 by mburl             #+#    #+#             */
/*   Updated: 2020/03/04 09:08:08 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cl_h.h"
#include <mlx.h>
#include "window.h"
#include "keys.h"
#include "visual.h"

t_compl		init_compl(const double re, const double im)
{
	t_compl	ret;

	ret.re = re;
	ret.im = im;
	return (ret);
}

void		draw_menu(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
	mlx_string_put(mlx->ptr, mlx->win, 460, 355,
		COLOR_WHITE, "Controls");
	mlx_string_put(mlx->ptr, mlx->win, 385, 400,
		COLOR_WHITE, "Itertations   - Arrow up / down");
	mlx_string_put(mlx->ptr, mlx->win, 385, 430,
		COLOR_WHITE, "Zoom          - Scroll");
	mlx_string_put(mlx->ptr, mlx->win, 385, 460,
		COLOR_WHITE, "Color         - 1..6 / B");
	mlx_string_put(mlx->ptr, mlx->win, 385, 490,
		COLOR_WHITE, "Fractals      - P / N");
	mlx_string_put(mlx->ptr, mlx->win, 385, 520,
		COLOR_WHITE, "Reset         - R");
	mlx_string_put(mlx->ptr, mlx->win, 385, 550,
		COLOR_WHITE, "Exit          - ESC");
}
