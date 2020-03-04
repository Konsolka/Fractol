/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_other.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 16:35:07 by mburl             #+#    #+#             */
/*   Updated: 2020/03/04 14:18:22 by mburl            ###   ########.fr       */
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

void	fractol_init(t_fractol *f)
{
	f->s = 0;
	f->color = 1;
	f->xmin = -2.0;
	f->ymin = -2.0;
	f->xmax = 2.0;
	f->ymax = 2.0;
	f->k = init_compl(-0.4, 0.6);
}

void	set_init(t_mlx *mlx)
{
	cl_int	ret;

	ft_strdel(&mlx->cl->source_str);
	ret = clSetKernelArg(mlx->cl->kernel, 0,
			sizeof(cl_mem), (void *)&mlx->cl->mem_obj);
	terminate("clSetKernelArg_0", ret);
	ret = clSetKernelArg(mlx->cl->kernel, 1,
			sizeof(t_fractol), (void *)mlx->f);
	terminate("clSetKernelArg_1", ret);
	ret = clSetKernelArg(mlx->cl->kernel, 2,
			sizeof(char), (void *)&mlx->f->color);
	terminate("clSetKernelArg_2", ret);
	ret = clGetKernelWorkGroupInfo(mlx->cl->kernel,
			mlx->cl->device_id, CL_KERNEL_WORK_GROUP_SIZE,
			sizeof(size_t), &mlx->cl->local_s, 0);
	terminate("clGetKernelWorkGroupInfo", ret);
	ret = clEnqueueNDRangeKernel(mlx->cl->command_queue,
			mlx->cl->kernel, 1, NULL, &mlx->cl->global_s,
			&mlx->cl->local_s, 0, NULL, NULL);
	terminate("clEnqueueNDRangeKernel", ret);
}
