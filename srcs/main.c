/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:52:57 by mburl             #+#    #+#             */
/*   Updated: 2020/02/17 15:32:07 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <mlx.h>
#include "libft.h"
#include "visual.h"
#include "key_code.h"
#include "window.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif


void	mandelbrot_init(t_mlx *mlx)
{
	cl_int	ret;

	ret = clSetKernelArg(mlx->cl->kernel, 0, sizeof(cl_mem), (void *)&mlx->cl->mem_obj);
	terminate("clSetKernelArg_0", ret);
	ret = clSetKernelArg(mlx->cl->kernel, 1, sizeof(t_fractol), (void *)mlx->f);
	terminate("clSetKernelArg_1", ret);
	ret = clGetKernelWorkGroupInfo(mlx->cl->kernel, mlx->cl->device_id, CL_KERNEL_WORK_GROUP_SIZE,
									sizeof(size_t), &mlx->cl->local_s, 0);
	terminate("clGetKernelWorkGroupInfo", ret);
	ret = clEnqueueNDRangeKernel(mlx->cl->command_queue, mlx->cl->kernel, 1, NULL,
			&mlx->cl->global_s, &mlx->cl->local_s, 0, NULL, NULL);
	terminate("clEnqueueNDRangeKernel", ret);
	// a = x;
	// b = y;
}


void	image_put(t_mlx *mlx)
{
	char		*line;
	char		*num;

	mlx->img = (int *)mlx_new_image(mlx->ptr, WIDTH, HIEGHT);
	mlx->line = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_size, &mlx->ed);
	mandelbrot_init(mlx);
	mlx->cl->ret = clEnqueueReadBuffer(mlx->cl->command_queue, mlx->cl->mem_obj, CL_TRUE, 0, sizeof(int) * WIDTH * HIEGHT,
			mlx->line, 0, NULL, NULL);
	terminate("clEnqueueReadBuffer", mlx->cl->ret);
	mlx->cl->ret = clFlush(mlx->cl->command_queue);
    mlx->cl->ret = clFinish(mlx->cl->command_queue);
	if (mlx->menu)
		draw_menu(mlx);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
	if (mlx->menu)
		draw_menu_strings(mlx);
	line = ft_strdup("Iterations = ");
	num = ft_itoa(mlx->f->iter);
	line = ft_strcat(line, num);
	mlx_string_put(mlx->ptr, mlx->win, 20, 20, COLOR_WHITE, line);
	ft_strdel(&line);
	ft_strdel(&num);
	mlx_destroy_image(mlx->ptr, mlx->img);
}


char	*load_src(const char *const path)
{
	int		fd;
	char	*buf;
	char	*tmp;
	char	*src;

	src = NULL;
	if ((fd = open(path, O_RDONLY)) < 0)
		return (0);
	buf = (char *)ft_memalloc(sizeof(char) * 100);
	while (read(fd, buf, 99) > 0)
	{
		if (!src)
			src = ft_strdup(buf);
		else
		{
			tmp = src;
			src = ft_strjoin(tmp, buf);
			free(tmp);
		}
		ft_bzero(buf, 100);
	}
	close(fd);
	free(buf);
	return (src);
}

void	cl_init(t_opcl *cl, int set)
{
	if (!(cl->source_str = load_src("srcs/sets.cl")))
		terminate("Error: when reading a program.", 1);
	cl->source_size = ft_strlen(cl->source_str);
	cl->ret = clGetPlatformIDs(0, 0, &cl->ret_num_platforms);
	terminate("clGetPlatformIDs_0", cl->ret);
	cl->ret = clGetPlatformIDs(cl->ret_num_platforms, &cl->platform_id, 0);
	terminate("clGetPlatformIDs_1", cl->ret);
	cl->ret = clGetDeviceIDs(cl->platform_id, CL_DEVICE_TYPE_GPU, 0, 0, &cl->ret_num_devices);
	terminate("clGetDeviceIDs", cl->ret);
    cl->ret = clGetDeviceIDs(cl->platform_id, CL_DEVICE_TYPE_GPU, cl->ret_num_devices,
            &cl->device_id, 0);
	terminate("clGetDeviceIDs", cl->ret);
    cl->context = clCreateContext(0, 1, &cl->device_id, NULL, NULL, &cl->ret);
	terminate("clCreateContext", cl->ret);
	cl->command_queue = clCreateCommandQueue(cl->context, cl->device_id, 0, &cl->ret);
	terminate("clCreateCommandQueue", cl->ret);
	
    // Create a program from the kernel source

    cl->program = clCreateProgramWithSource(cl->context, 1, 
            (const char **)&cl->source_str, NULL, &cl->ret);
	terminate("clCreateProgramWithSource", cl->ret);
    // Build the program
    cl->ret = clBuildProgram(cl->program, 0, NULL, "-I includes/", NULL, NULL);
	if (cl->ret == CL_SUCCESS)
		fprintf(stdout, "clBuildProgram SUCCESS\n");
	else if (cl->ret == CL_BUILD_PROGRAM_FAILURE)
	{
		fprintf(stderr, "ERROR CL_BUILD_PROGRAM_FAILURE\n");
		clGetProgramBuildInfo(cl->program, cl->device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &cl->log_size);
		char *log = (char *) malloc(cl->log_size);
		clGetProgramBuildInfo(cl->program, cl->device_id, CL_PROGRAM_BUILD_LOG, cl->log_size, log, NULL);
		fprintf(stderr, "%s\n", log);
	}

    // Create the OpenCL kernel
	if (set == 1)
    	cl->kernel = clCreateKernel(cl->program, "mandelbrot_set", &cl->ret);
	else if (set == 2)
		cl->kernel = clCreateKernel(cl->program, "julia_set", &cl->ret);
	terminate("clCreateKernel", cl->ret);
	cl->global_s = WIDTH * HIEGHT;
	cl->mem_obj = clCreateBuffer(cl->context, CL_MEM_READ_ONLY,
			sizeof(int) * WIDTH * HIEGHT, NULL, &cl->ret);
	terminate("clCreateBuffer", cl->ret);
}

void	fractol_init(t_fractol *f)
{
	f->iter = 10;
	f->zoom = 1;
	f->j = 0;
	f->xmin = -2.5;
	f->ymin = -2.5;
	f->x = f->xmin;
	f->y = f->ymin;
	f->xmax = 2.5;
	f->ymax = 2.5;
	f->xmouse = 200;
	f->ymouse = 200;
	f->xmove = 0;
	f->ymove = 0;
	f->dx = (f->xmax - f->xmin) / WIDTH;
	f->dy = (f->ymax - f->ymin) / HIEGHT;
}

void	draw(int set)
{

	t_mlx	mlx;

	mlx.cl = ft_memalloc(sizeof(t_opcl));
	mlx.f = ft_memalloc(sizeof(t_fractol));
	cl_init(mlx.cl, set);
	fractol_init(mlx.f);
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
	if (ac != 2)
		ft_putstr_err("Usage:\t1: Mandelbrot\n\t2: Julia\n");
	draw(ft_atoi(av[1]));
	return (0);
}