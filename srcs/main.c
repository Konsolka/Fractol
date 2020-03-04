/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:52:57 by mburl             #+#    #+#             */
/*   Updated: 2020/03/04 09:26:08 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <mlx.h>
#include "libft.h"
#include "visual.h"
#include "cl_h.h"
#include "keys.h"
#include "window.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
# include <OpenCL/opencl.h>
#else
# include <CL/cl.h>
#endif

void	iterations_put(t_mlx *mlx)
{
	char		*line;
	char		*num;
	char		*temp;

	line = ft_strdup("Iterations = ");
	num = ft_itoa(mlx->f->iter);
	temp = line;
	line = ft_strjoin(temp, num);
	free(temp);
	mlx_string_put(mlx->ptr, mlx->win, 20, 20, COLOR_WHITE, line);
	if (mlx->menu)
		mlx_string_put(mlx->ptr, mlx->win, 20, 50,
			COLOR_WHITE, "Hide menu  - H");
	else
		mlx_string_put(mlx->ptr, mlx->win, 20, 50,
			COLOR_WHITE, "Show menu  - H");
	ft_strdel(&line);
	ft_strdel(&num);
}

void	image_put(t_mlx *mlx)
{
	mlx->img = (int *)mlx_new_image(mlx->ptr, WIDTH, HIEGHT);
	mlx->line = mlx_get_data_addr(mlx->img, &mlx->bpp,
				&mlx->line_size, &mlx->ed);
	if (!mlx->menu)
	{
		mlx->f->factor = init_compl((mlx->f->xmax - mlx->f->xmin) / (WIDTH - 1),
					(mlx->f->ymax - mlx->f->ymin) / (HIEGHT - 1));
		set_init(mlx);
		mlx->cl->ret = clEnqueueReadBuffer(mlx->cl->command_queue,
				mlx->cl->mem_obj, CL_TRUE, 0,
				sizeof(int) * WIDTH * HIEGHT, mlx->line, 0, NULL, NULL);
		terminate("clEnqueueReadBuffer", mlx->cl->ret);
		mlx->cl->ret = clFlush(mlx->cl->command_queue);
		mlx->cl->ret = clFinish(mlx->cl->command_queue);
		mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
	}
	else
		draw_menu(mlx);
	iterations_put(mlx);
	mlx_destroy_image(mlx->ptr, mlx->img);
}

void	re_draw(int set, t_mlx *mlx)
{
	mlx->set = set;
	mlx->cl->ret = clReleaseKernel(mlx->cl->kernel);
	terminate("clReleaseKernel", mlx->cl->ret);
	mlx->cl->ret = clReleaseProgram(mlx->cl->program);
	terminate("clReleaseProgram", mlx->cl->ret);
	mlx->cl->ret = clReleaseMemObject(mlx->cl->mem_obj);
	terminate("clReleaseMemObject", mlx->cl->ret);
	mlx->cl->ret = clReleaseCommandQueue(mlx->cl->command_queue);
	terminate("clReleaseCommandQueue", mlx->cl->ret);
	mlx->cl->ret = clReleaseContext(mlx->cl->context);
	terminate("clReleaseContext", mlx->cl->ret);
	mlx->change = 0;
	mlx->ani = 0;
	cl_init(mlx->cl, set);
	fractol_init(mlx->f);
	image_put(mlx);
}

void	draw(int set)
{
	t_mlx	mlx;

	mlx.cl = ft_memalloc(sizeof(t_opcl));
	mlx.f = ft_memalloc(sizeof(t_fractol));
	mlx.set = set;
	mlx.change = 0;
	mlx.ani = 0;
	cl_init(mlx.cl, set);
	fractol_init(mlx.f);
	mlx.f->iter = 50;
	mlx.ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.ptr, WIDTH, HIEGHT, TITLE);
	image_put(&mlx);
	mlx_hook(mlx.win, 4, 0, mouse_press, &mlx);
	mlx_hook(mlx.win, 2, 0, key_parce, &mlx);
	mlx_hook(mlx.win, 5, 0, mouse_release, &mlx);
	mlx_hook(mlx.win, 17, 0, win_close, &mlx);
	mlx_loop(mlx.ptr);
}

int		main(int ac, char **av)
{
	int		set;

	set = (ac == 2) ? ft_atoi(av[1]) : 0;
	if (0 < set && set < 4)
		draw(set);
	else
	{
		ft_putstr_err("Usage:\t./fractol [num]\n");
		ft_putstr_err("\t1: Mandelbrot\n");
		ft_putstr_err("\t2: Julia\n\t3: Burning Ship\n");
	}
	return (0);
}
