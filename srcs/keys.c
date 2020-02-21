/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 13:15:00 by mburl             #+#    #+#             */
/*   Updated: 2020/02/21 18:51:51 by mburl            ###   ########.fr       */
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
		if (button == MOUSE_SCROLL_DOWN)
			zoom = 1.2;
		else
			zoom = 0.8;
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

int		key_parce(int key, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (key == MAIN_PAD_ESC)
		win_close(mlx);
	else if (key == ARROW_UP)
			mlx->f->iter += 10;
	else if (key == ARROW_DOWN)
	{
		if (mlx->f->iter > 2)
			mlx->f->iter -= 10;
	}
	else if (key == 15)
		fractol_init(mlx->f);
	else if (key == 4 && !mlx->menu)
		mlx->menu = 1;
	else if (key == 4 && mlx->menu)
		mlx->menu = 0;
	else if (18 <= key && key <= 23)
		mlx->f->color = key - 17;
	else if (key == 35 || key == 45)
	{
		mlx->change = 1;
		mlx->set += (key == 35) ? 1 : -1;
		if (mlx->set > 2)
			mlx->set = 1;
		else if (mlx->set < 1)
			mlx->set = 2;
		re_draw(mlx->set, mlx);
	}
	else if (key == KEY_B)
	{
		if (mlx->f->s)
			mlx->f->s = 0;
		else
			mlx->f->s = 1;
	}
	if (key != 35 || key != 45)
		image_put(mlx);
	return (0);
}

int		win_close(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	mlx_clear_window(mlx->ptr, mlx->win);
	mlx_destroy_window(mlx->ptr, mlx->win);
	ft_memdel((void **)&mlx->f);
	ft_strdel(&mlx->cl->source_str);
    mlx->cl->ret = clReleaseKernel(mlx->cl->kernel);
    mlx->cl->ret = clReleaseProgram(mlx->cl->program);
    mlx->cl->ret = clReleaseMemObject(mlx->cl->mem_obj);
    mlx->cl->ret = clReleaseCommandQueue(mlx->cl->command_queue);
    mlx->cl->ret = clReleaseContext(mlx->cl->context);
	ft_memdel((void **)&mlx->cl);
	ft_putstr("exiting\n");
	exit(0);
}