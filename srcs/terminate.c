/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 11:27:02 by mburl             #+#    #+#             */
/*   Updated: 2020/02/28 16:19:40 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "visual.h"
#include "cl_h.h"
#include "libft.h"
#include <mlx.h>

void	terminate(char *string, cl_int ret)
{
	char	*err_num;

	err_num = NULL;
	if (ret == CL_SUCCESS)
		return ;
	err_num = ft_itoa(ret);
	err_num = ft_strjoin(" ", err_num);
	ft_putstr("ERROR in ");
	ft_putstr(string);
	ft_putchar('\n');
	ft_putstr(err_num);
	ft_strdel(&err_num);
	if (ret != CL_SUCCESS)
		exit(-1);
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
