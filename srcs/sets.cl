#include "cl_h.h"
#include "window.h"

double			ft_map(double value, double start_range, double end_range,
					double new_range_start, double new_range_end)
{
	return ((value - start_range) / (end_range - start_range) *
				(new_range_end - new_range_start) + new_range_start);
}

__kernel void	mandelbrot_set(__global int *data, t_fractol f)
{
	int			iter;
	long		color;
	int			temp;
	double		x;
	double		y;
	double		a;
	double		b;
	double		aa;
	double		bb;
	double		ca;
	double		cb;
	double		twoab;

	temp = get_global_id(0);
	x = temp % WIDTH;
	y = temp / HIEGHT;
	a = (ft_map(x, 0, WIDTH, f.xmin, f.xmax) + f.xmove) / f.zoom;
	b = (ft_map(y, 0, HIEGHT, f.ymin, f.ymax) + f.ymove) / f.zoom;
	ca = a;
	cb = b;
	iter = 0;
	while (iter < f.iter)
	{
		aa = a * a;
		bb = b * b;
		twoab = 2 * a * b;
		if (aa + bb > 4.0)
			break ;
		a = aa - bb + ca;
		b = twoab + cb;
		iter++;
	}
	color = ft_map(iter, 0, f.iter, 0, 255);
	if (iter == f.iter)
		color = COLOR_WHITE;
	data[temp] = color;
}

__kernel void	julia_set(__global int *data, t_fractol f)
{
	int			iter;
	long		color;
	int			temp;
	double		x;
	double		y;
	double		a;
	double		b;
	double		aa;
	double		bb;
	double		ca;
	double		cb;
	double		twoab;

	temp = get_global_id(0);
	// ca = ft_map(f.xmouse, 0, WIDTH, -2.5, 2.5);
	// cb = ft_map(f.ymouse, 0, HIEGHT, -2.5, 2.5);
	ca = ft_map(f.xmouse, 0, WIDTH, f.xmin, f.xmax);
	cb = ft_map(f.ymouse, 0, HIEGHT, f.ymin, f.ymax);
	x = temp % WIDTH;
	y = temp / HIEGHT;
	a = f.xmin + f.dx * x;
	b = f.ymin + f.dy * y;
	iter = 0;
	while (iter < f.iter)
	{
		aa = a * a;
		bb = b * b;
		if (aa + bb > 4.0)
			break ;
		twoab = 2 * a * b;
		a = aa - bb + ca;
		b = twoab + cb;
		iter++;
	}
	color = ft_map(iter, 0, f.iter, 0, 255);
	if (iter == f.iter)
		color = COLOR_WHITE;
	data[temp] = color;
}