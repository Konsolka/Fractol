/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:52:57 by mburl             #+#    #+#             */
/*   Updated: 2020/01/28 17:47:47 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <mlx.h>
#include "libft.h"
#include "visual.h"
#include "key_code.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

void	data_to_mlx(t_mlx *mlx, int long *data)
{
	int		i;

	i = 0;
	while (i < WIDTH * HIEGHT)
	{
		mlx->line[i] = data[i];
		i++;
	}
}

void	mandelbrot_int(t_mlx *mlx, cl_command_queue command_queue,
					cl_kernel kernel, size_t *global_item_size,
					cl_mem mlx_mem_obj, cl_mem *line_mem_obj, cl_device_id device_id)
{
	int			temp;
	int long	color;
	size_t		local_item_size;
	double		w;
	double		h;
	int			iter;
	int			ret;


	// dx = (mlx->xmax - mlx->xmin) / WIDTH;
	// dy = (mlx->ymax - mlx->ymin) / HIEGHT;
	// ca = ft_map(mlx->xmouse, 0, WIDTH, -1, 1);
	// cb = ft_map(mlx->ymouse, 0, HIEGHT, -1, 1);
	// y = mlx->ymin;

	ret = clSetKernelArg(kernel, 0, sizeof(t_mlx *), (void *)mlx);
	if (ret == CL_SUCCESS)
		fprintf(stdout, "clSetKernelArg Success\n");
	else if (ret == CL_INVALID_KERNEL)
		fprintf(stderr, "CL_INVALID_KERNEL\n");
	else if (ret == CL_INVALID_ARG_INDEX)
		fprintf(stderr, "CL_INVALID_ARG_INDEX\n");
	else if (ret == CL_INVALID_ARG_VALUE)
		fprintf(stderr, "CL_INVALID_ARG_VALUE\n");
	else if (ret == CL_INVALID_MEM_OBJECT)
		fprintf(stderr, "CL_INVALID_MEM_OBJECT\n");
	else if (ret == CL_INVALID_SAMPLER)
		fprintf(stderr, "CL_INVALID_SAMPLER\n");
	else if (ret == CL_INVALID_ARG_SIZE)
		fprintf(stderr, "CL_INVALID_ARG_SIZE\n");

	ret = clSetKernelArg(kernel, 1, sizeof(char *), (void *)line_mem_obj);
	if (ret == CL_SUCCESS)
		fprintf(stdout, "clSetKernelArg Success\n");
	else if (ret == CL_INVALID_KERNEL)
		fprintf(stderr, "CL_INVALID_KERNEL\n");
	else if (ret == CL_INVALID_ARG_INDEX)
		fprintf(stderr, "CL_INVALID_ARG_INDEX\n");
	else if (ret == CL_INVALID_ARG_VALUE)
		fprintf(stderr, "CL_INVALID_ARG_VALUE\n");
	else if (ret == CL_INVALID_MEM_OBJECT)
		fprintf(stderr, "CL_INVALID_MEM_OBJECT\n");
	else if (ret == CL_INVALID_SAMPLER)
		fprintf(stderr, "CL_INVALID_SAMPLER\n");
	else if (ret == CL_INVALID_ARG_SIZE)
		fprintf(stderr, "CL_INVALID_ARG_SIZE\n");

	ret = clGetKernelWorkGroupInfo(kernel, device_id, CL_KERNEL_WORK_GROUP_SIZE, sizeof(local_item_size), &local_item_size, NULL);
	if (ret == CL_SUCCESS)
		fprintf(stdout, "clGetKernelWorkGroupInfo Success\n");
	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL,
			global_item_size, &local_item_size, 0, NULL, NULL);
	if (ret == CL_INVALID_COMMAND_QUEUE)
		fprintf(stderr, "ERROR CL_INVALID_COMMAND_QUEUE\n");
	else if (ret == CL_INVALID_CONTEXT)
		fprintf(stderr, "ERROR CL_INVALID_CONTEXT\n");
	else if (ret == CL_INVALID_MEM_OBJECT)
		fprintf(stderr, "ERROR CL_INVALID_MEM_OBJECT\n");
	else if (ret == CL_INVALID_VALUE)
		fprintf(stderr, "ERROR CL_INVALID_VALUE\n");
	else if (ret == CL_INVALID_EVENT_WAIT_LIST)
		fprintf(stderr, "ERROR CL_INVALID_EVENT_WAIT_LIST\n");
	else if (ret == CL_MEM_OBJECT_ALLOCATION_FAILURE)
		fprintf(stderr, "ERROR CL_MEM_OBJECT_ALLOCATION_FAILURE\n");
	else if (ret == CL_OUT_OF_HOST_MEMORY)
		fprintf(stderr, "ERROR CL_OUT_OF_HOST_MEMORY\n");
	
	// a = x;
	// b = y;
}


void	image_put(t_mlx *mlx)
{
	char		*line;
	char		*num;
    FILE *fp;
    char *source_str;
    size_t source_size;
    cl_platform_id platform_id;
    cl_device_id device_id;   
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;

	platform_id = NULL;
	device_id = NULL;
	
	// Load the kernel source code into the array source_str
    fp = fopen("srcs/sets.cl", "r");
    if (!fp)
	{
        fprintf(stderr, "Failed to load kernel.\n");
        exit(1);
    }
	mlx->img = mlx_new_image(mlx->ptr, WIDTH, HIEGHT);
	mlx->line = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_size, &mlx->ed);
    source_str = (char*)malloc(MAX_SOURCE_SIZE);
    source_size = fread( source_str, 1, MAX_SOURCE_SIZE, fp);
    fclose( fp );

    // Get platform and device information
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	if (ret == CL_SUCCESS)
		fprintf(stdout, "clGetPlatformIDs Succsess\n");

    ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_ALL, 1, 
            &device_id, &ret_num_devices);
	if (ret == CL_SUCCESS)
		fprintf(stdout, "clGetDeviceIDs Succsess\n");
	else if (ret == CL_INVALID_PLATFORM)
		fprintf(stderr, "Error CL_INVALID_PLATFORM\n");
	else if (ret == CL_INVALID_DEVICE_TYPE)
		fprintf(stderr, "Error CL_INVALID_DEVICE_TYPE\n");
	else if (ret == CL_INVALID_VALUE)
		fprintf(stderr, "Error CL_INVALID_VALUE\n");
	else if (ret == CL_DEVICE_NOT_FOUND)
		fprintf(stderr, "Error CL_DEVICE_NOT_FOUND\n");

    // Create an OpenCL context
    cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);
	if (ret == CL_SUCCESS)
		fprintf(stdout, "clCreateContext Succsess\n");
    // Create a command queue
    cl_command_queue command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
	if (ret == CL_SUCCESS)
		fprintf(stdout, "clCreateCommandQueue Succsess\n");
	else
		fprintf(stderr, "clCreateCommandQueue ERROR\n");

    // Create memory buffers on the device for each vector 
    cl_mem mlx_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, 
            sizeof(t_mlx *), NULL, &ret);
	cl_mem line_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
			WIDTH * HIEGHT * sizeof(char), NULL, &ret);
	if (ret == CL_SUCCESS)
		fprintf(stdout, "clCreateBuffer Succsess\n");
	else if (ret == CL_INVALID_CONTEXT)
		fprintf(stderr, "Error CL_INVALID_CONTEXT\n");
	else if (ret == CL_INVALID_VALUE)
		fprintf(stderr, "Error CL_INVALID_VALUE\n");
	else if (ret == CL_INVALID_BUFFER_SIZE)
		fprintf(stderr, "Error CL_INVALID_BUFFER_SIZE\n");
	else if (ret == CL_INVALID_HOST_PTR)
		fprintf(stderr, "Error CL_INVALID_HOST_PTR\n");
	else if (ret == CL_MEM_OBJECT_ALLOCATION_FAILURE)
		fprintf(stderr, "Error CL_MEM_OBJECT_ALLOCATION_FAILURE\n");
	else if (ret == CL_OUT_OF_HOST_MEMORY)
		fprintf(stderr, "Error CL_OUT_OF_HOST_MEMORY\n");
	// cl_mem	data_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
	// 		sizeof(int) * WIDTH * HIEGHT, NULL, &ret);
	// if (ret == CL_SUCCESS)
	// 	fprintf(stdout, "clCreateBuffer Succsess\n");
	// else if (ret == CL_INVALID_CONTEXT)
	// 	fprintf(stderr, "Error CL_INVALID_CONTEXT\n");
	// else if (ret == CL_INVALID_VALUE)
	// 	fprintf(stderr, "Error CL_INVALID_VALUE\n");
	// else if (ret == CL_INVALID_BUFFER_SIZE)
	// 	fprintf(stderr, "Error CL_INVALID_BUFFER_SIZE\n");
	// else if (ret == CL_INVALID_HOST_PTR)
	// 	fprintf(stderr, "Error CL_INVALID_HOST_PTR\n");
	// else if (ret == CL_MEM_OBJECT_ALLOCATION_FAILURE)
	// 	fprintf(stderr, "Error CL_MEM_OBJECT_ALLOCATION_FAILURE\n");
	// else if (ret == CL_OUT_OF_HOST_MEMORY)
	// 	fprintf(stderr, "Error CL_OUT_OF_HOST_MEMORY\n");

	
    // Copy the lists A and B to their respective memory buffers
	// ret = clEnqueueWriteBuffer(command_queue, line_mem_obj, CL_TRUE, 0,
	// 		sizeof(mlx->line), mlx->line, 0, NULL, NULL);
	// ret = clEnqueueWriteBuffer(command_queue, data_mem_obj, CL_TRUE, 0,
	// 		sizeof(int) * WIDTH * HIEGHT, mlx->data, 0, NULL, NULL);
    // ret = clEnqueueWriteBuffer(command_queue, mlx_mem_obj, CL_TRUE, 0,
    //         sizeof(t_mlx *), (void *)&mlx, 0, NULL, NULL);
	// if (ret == CL_SUCCESS)
	// 	fprintf(stdout, "clEnqueueWriteBuffer Succsess\n");
	// else if (ret == CL_INVALID_COMMAND_QUEUE)
	// 	fprintf(stderr, "ERROR CL_INVALID_COMMAND_QUEUE\n");
	// else if (ret == CL_INVALID_CONTEXT)
	// 	fprintf(stderr, "ERROR CL_INVALID_CONTEXT\n");
	// else if (ret == CL_INVALID_MEM_OBJECT)
	// 	fprintf(stderr, "ERROR CL_INVALID_MEM_OBJECT\n");
	// else if (ret == CL_INVALID_VALUE)
	// 	fprintf(stderr, "ERROR CL_INVALID_VALUE\n");
	// else if (ret == CL_INVALID_EVENT_WAIT_LIST)
	// 	fprintf(stderr, "ERROR CL_INVALID_EVENT_WAIT_LIST\n");
	// else if (ret == CL_MEM_OBJECT_ALLOCATION_FAILURE)
	// 	fprintf(stderr, "ERROR CL_MEM_OBJECT_ALLOCATION_FAILURE\n");
	// else if (ret == CL_OUT_OF_HOST_MEMORY)
	// 	fprintf(stderr, "ERROR CL_OUT_OF_HOST_MEMORY\n");

	
    // Create a program from the kernel source
    cl_program program = clCreateProgramWithSource(context, 1, 
            (const char **)&source_str, (const size_t *)&source_size, &ret);
	if (ret == CL_SUCCESS)
		fprintf(stdout, "clCreateProgramWithSource Succsess\n");	
	else if (ret == CL_INVALID_CONTEXT)
		fprintf(stderr, "ERROR CL_INVALID_CONTEXT\n");
	else if (ret == CL_INVALID_VALUE)
		fprintf(stderr, "ERROR CL_INVALID_VALUE\n");
	else if (ret == CL_OUT_OF_HOST_MEMORY)
		fprintf(stderr, "ERROR CL_OUT_OF_HOST_MEMORY\n");

    // Build the program
	size_t	log_size;
    ret = clBuildProgram(program, 1, &device_id, "-I includes/", NULL, NULL);
	if (ret == CL_SUCCESS)
		fprintf(stdout, "clBuildProgram Succsess\n");
	else if (ret == CL_INVALID_PROGRAM)
		fprintf(stderr, "ERROR CL_INVALID_PROGRAM\n");
	else if (ret == CL_INVALID_VALUE)
		fprintf(stderr, "ERROR CL_INVALID_VALUE\n");
	else if (ret == CL_INVALID_DEVICE)
		fprintf(stderr, "ERROR CL_INVALID_DEVICE\n");
	else if (ret == CL_INVALID_BINARY)
		fprintf(stderr, "ERROR CL_INVALID_BINARY\n");
	else if (ret == CL_INVALID_BUILD_OPTIONS)
		fprintf(stderr, "ERROR CL_INVALID_BUILD_OPTIONS\n");
	else if (ret == CL_INVALID_OPERATION)
		fprintf(stderr, "ERROR CL_INVALID_OPERATION\n");
	else if (ret == CL_COMPILER_NOT_AVAILABLE)
		fprintf(stderr, "ERROR CL_COMPILER_NOT_AVAILABLE\n");
	else if (ret == CL_BUILD_PROGRAM_FAILURE)
	{
		fprintf(stderr, "ERROR CL_BUILD_PROGRAM_FAILURE\n");
		clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
		char *log = (char *) malloc(log_size);
		clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
		fprintf(stderr, "%s\n", log);
	}
	else if (ret == CL_INVALID_OPERATION)
		fprintf(stderr, "ERROR CL_INVALID_OPERATION\n");
	else if (ret == CL_OUT_OF_HOST_MEMORY)
		fprintf(stderr, "ERROR CL_OUT_OF_HOST_MEMORY\n");

    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "mandelbrot_set", &ret);
	if (ret == CL_INVALID_PROGRAM)
		fprintf(stderr, "ERROR invalid program\n");
	else if (ret == CL_INVALID_PROGRAM_EXECUTABLE)
		fprintf(stderr, "ERROR CL_INVALID_PROGRAM_EXECUTABLE\n");
	else if (ret == CL_INVALID_KERNEL_NAME)
		fprintf(stderr, "ERROR CL_INVALID_KERNEL_NAME\n");
	else if (ret == CL_INVALID_KERNEL_DEFINITION)
		fprintf(stderr, "ERROR CL_INVALID_KERNEL_DEFINITION\n");
	else if (ret == CL_INVALID_VALUE)
		fprintf(stderr, "ERROR CL_INVALID_VALUE\n");
	else if (ret == CL_OUT_OF_HOST_MEMORY)
		fprintf(stderr, "ERROR CL_OUT_OF_HOST_MEMORY\n");



    // Set the arguments of the kernel
    

	size_t global_item_size = WIDTH * HIEGHT;
	// Execute the OpenCL kernel on the list



	double w = 5;
	double h = (w * HIEGHT) / WIDTH;
	mlx->dx = 1.0;
	mlx->dy = 1.0;
	mlx->y = 0;
	mlx->j = 0;
	mlx->xmin = -w / 2;
	mlx->ymin = -h / 2;
	mlx->xmax = mlx->xmin + w;
	mlx->ymax = mlx->ymin + h;
	mandelbrot_int(mlx, command_queue, kernel, &global_item_size, mlx_mem_obj, &line_mem_obj, device_id);
	ret = clEnqueueReadBuffer(command_queue, line_mem_obj, CL_TRUE, 0, WIDTH * HIEGHT,
			(void *)mlx->line, 0, NULL, NULL);
	printf("%s\n", mlx->line);







    // Clean up
    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(mlx_mem_obj);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);


	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
	line = ft_strdup("Iterations = ");
	num = ft_itoa(mlx->iter);
	line = ft_strcat(line, num);
	mlx_string_put(mlx->ptr, mlx->win, 20, 20, COLOR_WHITE, line);
	ft_strdel(&line);
	ft_strdel(&num);
	mlx_destroy_image(mlx->ptr, mlx->img);
}

void	draw(void)
{

	t_mlx	mlx;

	fprintf(stdout, "1 = %lu\n", sizeof(mlx));
	mlx.ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.ptr, WIDTH, HIEGHT, TITLE);
	mlx.iter = 10;
	mlx.xmouse = 200;
	mlx.zoom = 1;
	mlx.ymouse = 200;
	mlx.xmove = 0;
	mlx.test = 'a';
	mlx.ymove = 0;
	fprintf(stdout, "2 = %lu\n", sizeof(mlx));
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