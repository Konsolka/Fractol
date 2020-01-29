#include "cl_h.h"
#include "window.h"

double		ft_map(double value, double start_range, double end_range,
					double new_range_start, double new_range_end)
{
	return ((value - start_range) / (end_range - start_range) *
				(new_range_end - new_range_start) + new_range_start);
}

__kernel void mandelbrot_set(__global int *data, t_fractol f)
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
		aa = a * a - b * b;
		bb = 2 * a * b;
		if (a * a + b * b > 4.0)
			break ;
		a = aa + ca;
		b = bb + cb;
		iter++;
	}
	color = (long)(ft_map(iter, 0, f.iter, 0, 255));
	if (iter == f.iter)
		color = COLOR_WHITE;
	data[temp] = color;
}