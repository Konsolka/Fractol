/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 16:07:20 by mburl             #+#    #+#             */
/*   Updated: 2020/03/04 09:56:20 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __APPLE__
# include <OpenCL/opencl.h>
#else
# include <CL/cl.h>
#endif
#include "visual.h"
#include "libft.h"
#include "window.h"

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

void	kernel_init(t_opcl *cl, int set)
{
	if (set == 1)
		cl->kernel = clCreateKernel(cl->program, "mandelbrot_set", &cl->ret);
	else if (set == 2)
		cl->kernel = clCreateKernel(cl->program, "julia_set", &cl->ret);
	else if (set == 3)
		cl->kernel = clCreateKernel(cl->program, "burning_ship", &cl->ret);
	terminate("clCreateKernel", cl->ret);
	cl->global_s = WIDTH * HIEGHT;
}

void	cl_build_program(t_opcl *cl)
{
	char	*log;

	cl->source_size = ft_strlen(cl->source_str);
	cl->program = clCreateProgramWithSource(cl->context, 1,
			(const char **)&cl->source_str, NULL, &cl->ret);
	terminate("clCreateProgramWithSource", cl->ret);
	cl->ret = clBuildProgram(cl->program, 0, NULL, "-I includes/", NULL, NULL);
	if (cl->ret == CL_BUILD_PROGRAM_FAILURE)
	{
		clGetProgramBuildInfo(cl->program, cl->device_id,
				CL_PROGRAM_BUILD_LOG, 0, NULL, &cl->log_size);
		log = (char *)malloc(cl->log_size);
		clGetProgramBuildInfo(cl->program, cl->device_id,
				CL_PROGRAM_BUILD_LOG, cl->log_size, log, NULL);
		ft_putendl(log);
	}
	terminate("clBuildProgram", cl->ret);
}

void	cl_init(t_opcl *cl, int set)
{
	ft_strdel(&cl->source_str);
	if (!(cl->source_str = load_src("srcs/sets.cl")))
		terminate("Error: when reading a program.", 1);
	cl->ret = clGetPlatformIDs(0, 0, &cl->ret_num_platforms);
	terminate("clGetPlatformIDs_0", cl->ret);
	cl->ret = clGetPlatformIDs(cl->ret_num_platforms, &cl->platform_id, 0);
	terminate("clGetPlatformIDs_1", cl->ret);
	cl->ret = clGetDeviceIDs(cl->platform_id, CL_DEVICE_TYPE_GPU,
			0, 0, &cl->ret_num_devices);
	terminate("clGetDeviceIDs", cl->ret);
	cl->ret = clGetDeviceIDs(cl->platform_id, CL_DEVICE_TYPE_GPU,
			cl->ret_num_devices,
			&cl->device_id, 0);
	terminate("clGetDeviceIDs", cl->ret);
	cl->context = clCreateContext(0, 1, &cl->device_id, NULL, NULL, &cl->ret);
	terminate("clCreateContext", cl->ret);
	cl->command_queue = clCreateCommandQueue(cl->context,
				cl->device_id, 0, &cl->ret);
	cl_build_program(cl);
	terminate("clCreateCommandQueue", cl->ret);
	kernel_init(cl, set);
	cl->mem_obj = clCreateBuffer(cl->context, CL_MEM_READ_ONLY,
			sizeof(int) * WIDTH * HIEGHT, NULL, &cl->ret);
	terminate("clCreateBuffer", cl->ret);
}
