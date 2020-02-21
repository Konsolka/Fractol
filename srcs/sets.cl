#include "cl_h.h"
#include "window.h"

double			ft_map(double value, double start_range, double end_range,
						double new_range_start, double new_range_end)
{
	return ((value - start_range) / (end_range - start_range) *
				(new_range_end - new_range_start) + new_range_start);
}

int set_colors(unsigned char o, unsigned char red, \
				unsigned char green, unsigned char blue)
{
	int i;
	int tmp;
	int res;
	int j;

	i = 0;
	res = 0;
	tmp = 0;
	j = 0;
	while (i <= 31)
	{
		tmp = (i >= 0 && i <= 7) ? blue : tmp;
		tmp = (i >= 8 && i <= 15) ? green : tmp;
		tmp = (i >= 16 && i <= 23) ? red : tmp;
		tmp = (i >= 24 && i <= 31) ? o : tmp;
		j = 0;
		while (j <= 7)
		{
			if (tmp & (1 << j))
			res |= 1 << i;
			++i;
			++j;
		}
	}
	return (res);
}

int		choose_color(int i, int max, char color, int s)
{
	int			red;
	int			blue;
	int			green;
	double		n;

	n = (double)i / (double)max;
	if (s)
	{
		red = (int)(4 / n * 255);
		green = (int)(2 / n * 255);
		blue = (int)(3 / n * 255);
	}
	else
	{
		red = (int)(9 * (1 - n) * (n * n * n) * 255);
		green = (int)(2 * ((1 - n) * (1 - n)) * (n * n) * 255);
		blue = (int)(8.5 * ((1 - n) * (1 - n) * (1 - n)) * n * 255);
	}
	if (color == 1)
		return (set_colors(0, red, green, blue));
	else if (color == 2)
	 	return (set_colors(0, red, blue, green));
	else if (color == 3)
		return (set_colors(0, blue, red, green));
	else if (color == 4)
		return (set_colors(0, blue, green, red));
	else if (color == 5)
	 	return (set_colors(0, green, blue, red));
	else if (color == 6)
	 	return (set_colors(0, green, red, blue));
	return (0);
}

__kernel void	mandelbrot_set(__global int *data, t_fractol f, int color)
{
	int			iter;
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
	f.c.im = f.ymax - y * f.factor.im;
	f.c.re = f.xmin + x * f.factor.re;
	a = f.c.re;
	b = f.c.im;
	ca = a;
	cb = b;
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
	if (iter < f.iter)
 		data[temp] = choose_color(iter, f.iter, color, f.s);
 	else
        data[temp] = 0;
}

__kernel void	julia_set(__global int *data, t_fractol f, int color)
{
	int			iter;
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
	a = f.xmin + x * f.factor.re;
	b = f.ymax - y * f.factor.im;
	iter = 0;
	while (iter < f.iter)
	{
		aa = a * a;
		bb = b * b;
		if (aa + bb > 4.0)
			break ;
		twoab = 2 * a * b;
		a = aa - bb + f.k.re;
		b = twoab + f.k.im;
		iter++;
	}
	if (iter < f.iter)
 		data[temp] = choose_color(iter, f.iter, color, f.s);
 	else
        data[temp] = 0;
}