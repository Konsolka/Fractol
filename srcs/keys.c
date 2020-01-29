/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 13:15:00 by mburl             #+#    #+#             */
/*   Updated: 2020/01/29 18:32:13 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include "visual.h"
#include "libft.h"
#include "key_code.h"
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
	// t_mlx	*mlx;

	// if (button == MOUSE_LEFT_BUTTON)
	// {
	// 	mlx = (t_mlx *)param;
	// 	mlx->xmouse = x;
	// 	mlx->ymouse = y;
	// 	image_put(mlx);
	// 	mlx_hook(mlx->win, 6, 0, mouse_move_void, mlx);
	// }
	return (0);
}

int		mouse_move(int x, int y, void *param)
{
	// t_mlx	*mlx;

	// mlx = (t_mlx *)param;
	// mlx->xmouse = x;
	// mlx->ymouse = y;
	// image_put(mlx);
	return (0);
}

int		mouse_press(int button, int x, int y, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	fprintf(stdout, "x = %d | y = %d\nmap_x = %f | map_y = %f\n", x, y, ft_map(x, 0, WIDTH, -0.1, 0.1), ft_map(y, 0, HIEGHT, -0.1, 0.1));
	if (button == MOUSE_SCROLL_DOWN)
	{
		mlx->f->zoom *= 1.2;
		// mlx->f->xmove = WIDTH - (x / WIDTH * (WIDTH * mlx->f->zoom - WIDTH));
		// mlx->f->ymove = HIEGHT - (y / HIEGHT * (HIEGHT * mlx->f->zoom - HIEGHT));
		mlx->f->xmove += ft_map(x, 0, WIDTH, mlx->f->xmin, mlx->f->xmax);
		mlx->f->ymove += ft_map(x, 0, HIEGHT, mlx->f->ymin, mlx->f->ymax);
	}
	else if (button == MOUSE_SCROLL_UP)
	{
		if (mlx->f->zoom - 0.5 > 0)
		{
			mlx->f->zoom *= 0.8;
			mlx->f->xmove += ft_map(x, 0, WIDTH, mlx->f->xmin, mlx->f->xmax);
			mlx->f->ymove += ft_map(x, 0, HIEGHT, mlx->f->ymin, mlx->f->ymax);
		}
	}
	// else if (button == MOUSE_LEFT_BUTTON)
	// 	mlx_hook(mlx->win, 6, 0, mouse_move, mlx);
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
			mlx->f->iter++;
	else if (key == ARROW_DOWN)
	{
		if (mlx->f->iter > 2)
			mlx->f->iter--;
	}
	else if (key == 15)
	{
		mlx->f->xmove = 0;
		mlx->f->ymove = 0;
		mlx->f->zoom = 1;
		mlx->f->iter = 10;
	}
	else if (key == 4 && !mlx->menu)
		mlx->menu = 1;
	else if (key == 4 && mlx->menu)
		mlx->menu = 0;
	image_put(mlx);
	return (0);
}

int		win_close(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	mlx_clear_window(mlx->ptr, mlx->win);
	mlx_destroy_window(mlx->ptr, mlx->win);
    mlx->cl->ret = clReleaseKernel(mlx->cl->kernel);
    mlx->cl->ret = clReleaseProgram(mlx->cl->program);
    mlx->cl->ret = clReleaseMemObject(mlx->cl->mem_obj);
    mlx->cl->ret = clReleaseCommandQueue(mlx->cl->command_queue);
    mlx->cl->ret = clReleaseContext(mlx->cl->context);
	exit(0);
}