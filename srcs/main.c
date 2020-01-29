/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:52:57 by mburl             #+#    #+#             */
/*   Updated: 2020/01/29 16:41:22 by mburl            ###   ########.fr       */
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


	// dx = (mlx->xmax - mlx->xmin) / WIDTH;
	// dy = (mlx->ymax - mlx->ymin) / HIEGHT;
	// ca = ft_map(mlx->xmouse, 0, WIDTH, -1, 1);
	// cb = ft_map(mlx->ymouse, 0, HIEGHT, -1, 1);
	// y = mlx->ymin;

	ret = clSetKernelArg(mlx->cl->kernel, 0, sizeof(cl_mem), (void *)&mlx->cl->mem_obj);
	if (ret == CL_SUCCESS)
		fprintf(stdout, "clSetKernelArg Success\n");
	ret = clSetKernelArg(mlx->cl->kernel, 1, sizeof(t_fractol), mlx->f);
	if (ret == CL_SUCCESS)
		fprintf(stdout, "clSetKernelArg Success\n");


	ret = clGetKernelWorkGroupInfo(mlx->cl->kernel, mlx->cl->device_id, CL_KERNEL_WORK_GROUP_SIZE,
									sizeof(mlx->cl->local_s), &mlx->cl->local_s, NULL);
	if (ret == CL_SUCCESS)
		fprintf(stdout, "clGetKernelWorkGroupInfo Success\n");


	mlx->cl->local_s = 64;


	ret = clEnqueueNDRangeKernel(mlx->cl->command_queue, mlx->cl->kernel, 1, NULL,
			&mlx->cl->global_s, &mlx->cl->local_s, 0, NULL, NULL);
	if (ret == CL_SUCCESS)
		fprintf(stdout, "clEnqueueNDRangeKernel Succsess\n");		
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
	if (mlx->cl->ret == CL_SUCCESS)
		fprintf(stdout, "clEnqueueReadBuffer Success\n");

	mlx->cl->ret = clFlush(mlx->cl->command_queue);
    mlx->cl->ret = clFinish(mlx->cl->command_queue);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
	line = ft_strdup("Iterations = ");
	num = ft_itoa(mlx->f->iter);
	line = ft_strcat(line, num);
	mlx_string_put(mlx->ptr, mlx->win, 20, 20, COLOR_WHITE, line);
	ft_strdel(&line);
	ft_strdel(&num);
	mlx_destroy_image(mlx->ptr, mlx->img);

}

void	cl_init(t_opcl *cl)
{
	FILE	*fd;
	// Load the kernel source code into the array source_str
    fd = fopen("srcs/sets.cl", "r");
    if (!fd)
	{
        fprintf(stderr, "Failed to load kernel.\n");
        exit(1);
    }
    cl->source_str = (char*)malloc(MAX_SOURCE_SIZE);
    cl->source_size = fread(cl->source_str, 1, MAX_SOURCE_SIZE, fd);
    fclose(fd);
    // Get platform and device information
	cl->ret = clGetPlatformIDs(1, &cl->platform_id, &cl->ret_num_platforms);
	if (cl->ret == CL_SUCCESS)
		fprintf(stdout, "clGetPlatformIDs Succsess\n");

    cl->ret = clGetDeviceIDs(cl->platform_id, CL_DEVICE_TYPE_ALL, 1, 
            &cl->device_id, &cl->ret_num_devices);
    // Create an OpenCL context
    cl->context = clCreateContext( NULL, 1, &cl->device_id, NULL, NULL, &cl->ret);
    // Create a command queue
	cl->command_queue = clCreateCommandQueue(cl->context, cl->device_id, 0, &cl->ret);
    // Create memory buffers on the device for each vector 
	cl->mem_obj = clCreateBuffer(cl->context, CL_MEM_READ_ONLY,
			sizeof(int) * WIDTH * HIEGHT, NULL, &cl->ret);
	if (cl->ret == CL_SUCCESS)
		fprintf(stdout, "clCreateBuffer Succsess\n");
	
    // Create a program from the kernel source
    cl->program = clCreateProgramWithSource(cl->context, 1, 
            (const char **)&cl->source_str, (const size_t *)&cl->source_size, &cl->ret);
	if (cl->ret == CL_SUCCESS)
		fprintf(stdout, "clCreateProgramWithSource Succsess\n");	

    // Build the program
    cl->ret = clBuildProgram(cl->program, 1, &cl->device_id, "-I includes/", NULL, NULL);
	if (cl->ret == CL_SUCCESS)
		fprintf(stdout, "clBuildProgram Succsess\n");
	else if (cl->ret == CL_BUILD_PROGRAM_FAILURE)
	{
		fprintf(stderr, "ERROR CL_BUILD_PROGRAM_FAILURE\n");
		clGetProgramBuildInfo(cl->program, cl->device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &cl->log_size);
		char *log = (char *) malloc(cl->log_size);
		clGetProgramBuildInfo(cl->program, cl->device_id, CL_PROGRAM_BUILD_LOG, cl->log_size, log, NULL);
		fprintf(stderr, "%s\n", log);
	}

    // Create the OpenCL kernel
    cl->kernel = clCreateKernel(cl->program, "mandelbrot_set", &cl->ret);
	if (cl->ret == CL_SUCCESS)
		fprintf(stdout, "clCreateKernel Success\n");
	cl->global_s = WIDTH * HIEGHT;
}

void	fractol_init(t_fractol *f)
{
	f->iter = 10;
	f->zoom = 1;
	f->dx = 1.0;
	f->dy = 1.0;
	f->y = 0;
	f->j = 0;
	f->xmin = -2.5;
	f->ymin = -2.5;
	f->xmax = 2.5;
	f->ymax = 2.5;
	f->xmouse = 200;
	f->ymouse = 200;
	f->xmove = 0;
	f->ymove = 0;
}

void	draw(void)
{

	t_mlx	mlx;

	mlx.cl = ft_memalloc(sizeof(t_opcl));
	mlx.f = ft_memalloc(sizeof(t_fractol));
	cl_init(mlx.cl);
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

int		main(void)
{
	draw();
	return (0);
}