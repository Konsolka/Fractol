#include "visual.h"
#include "cl_h.h"

double		ft_map(double value, double start_range, double end_range,
					double new_range_start, double new_range_end)
{
	return ((value - start_range) / (end_range - start_range) *
				(new_range_end - new_range_start) + new_range_start);
}

__kernel void mandelbrot_set(__global t_mlx *mlx, __global int *data)
{
	int			iter;
	int long	color;
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
	
	printf("OK");
	temp = get_global_id(0);
	printf("iter = %d\n", mlx->iter);
	x = temp % WIDTH;
	y = temp / HIEGHT;
	a = (ft_map(x, 0, WIDTH, mlx->xmin, mlx->xmax) + mlx->xmove) / mlx->zoom;
	b = (ft_map(y, 0, HIEGHT, mlx->ymin, mlx->ymax) + mlx->ymove) / mlx->zoom;
	iter = 0;
	while (iter < mlx->iter)
	{
		ca = a;
		cb = b;
		aa = a * a;
		bb = b * b;
		if (aa + bb > 4.0)
			break ;
		twoab = 2.0 * a * b;
		a = aa - bb + ca;
		b = twoab + cb;
		iter++;
	}
	color = ft_map(iter, 0, mlx->iter, 0, 255);
	if (iter == mlx->iter)
		color = COLOR_WHITE;
	data[temp] = color;
}