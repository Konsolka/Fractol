/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 16:34:04 by mburl             #+#    #+#             */
/*   Updated: 2020/02/17 14:38:57 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIS_H

# define VIS_H

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

# define MAX_SOURCE_SIZE (0x100000)

typedef struct			s_opcl
{
	size_t				wgs;
    char				*source_str;
	cl_device_id		device_id;
	cl_command_queue	command_queue;
	cl_context			context;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				mem_obj;
	cl_platform_id		platform_id; 
	cl_uint				ret_num_devices;
	cl_uint				ret_num_platforms;
    size_t				source_size;
	size_t				global_s;
	size_t				local_s;
	cl_int				ret;
	size_t				log_size;
}						t_opcl;

typedef struct	s_fractol
{
	int		iter;
	int		i;
	int		j;
	double	xmin;
	double	ymin;
	double	xmax;
	double	ymax;
	double	zoom;
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	aa;
	double	bb;
	double	a;
	double	b;
	double	ca;
	double	cb;
	double	xmouse;
	double	ymouse;
	double	xmove;
	double	ymove;
	double	twoab;
}				t_fractol;

typedef struct	s_point
{
	int		x;
	int		y;
}				t_point;

typedef	struct	s_mlx
{
	void		*ptr;
	void		*win;
	void		*img;
	int			bpp;
	int			line_size;
	int			ed;
	char		*line;
	char		test;
	int long	*data;
	int			menu;
	t_opcl		*cl;
	t_fractol	*f;
}				t_mlx;

void	image_put(t_mlx *mlx);
int		key_parce(int key, void *param);
int		mouse_move(int x, int y, void *param);
int		mouse_release(int button, int x, int y, void *param);
void	draw_menu_strings(t_mlx *mlx);
int		mouse_move_void(int x, int y, void *param);
int		mouse_press(int button, int x, int y, void *param);
void	draw_menu(t_mlx *mlx);
int		win_close(void *param);
void	terminate(char *string, cl_int ret);
#endif