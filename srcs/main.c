/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:52:57 by mburl             #+#    #+#             */
/*   Updated: 2020/01/27 19:21:44 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <mlx.h>
#include "libft.h"
#include "visual.h"
#include "key_code.h"

int mouse_press(int button, int x, int y, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	printf("x = %d | y = %d\nmap_x = %f | map_y = %f\n", x, y, ft_map(x, 0, WIDTH, 0, 100), ft_map(y, 0, WIDTH, 0, 100));
	if (button == MOUSE_SCROLL_DOWN)
	{
		mlx->min -= ft_map(x, 0, WIDTH, 0, 100);
		mlx->max += ft_map(y, 0, HIEGHT, 0, 100);
	}
	else if (button == MOUSE_SCROLL_UP)
	{
		mlx->min -= ft_map(x, 0, WIDTH, 0, 100);
		mlx->max += ft_map(y, 0, HIEGHT, 0, 100);
	}
	image_put(mlx);
}

int		key_parce(int key, void *param)
{
	t_mlx *mlx;

	mlx = (t_mlx *)param;
	if (key == MAIN_PAD_ESC)
		close(mlx);
	else if (key == ARROW_UP)
			mlx->iter++;
	else if (key == ARROW_DOWN)
	{
		if (mlx->iter > 2)
			mlx->iter--;
	}
	image_put(mlx);
	return (0);
}

int		close(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	mlx_clear_window(mlx->ptr, mlx->win);
	mlx_destroy_window(mlx->ptr, mlx->win);
	exit(0);
}

void	image_put(t_mlx *mlx)
{
	int			i;
	int			temp;
	double		x;
	double		y;
	double		aa;
	double		bb;
	double		a;
	double		b;
	double		ca;
	double		cb;
	int long	color;
	char		*line;
	char		*num;

	mlx->img = mlx_new_image(mlx->ptr, WIDTH, HIEGHT);
	mlx->line = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_size, &mlx->ed);
	x = 0.0;
	while (x < WIDTH)
	{
		y = 0.0;
		while (y < HIEGHT)
		{
			a = ft_map(x, mlx->min, mlx->max, -mlx->zoom, mlx->zoom);
			b = ft_map(y, mlx->min, mlx->max, -mlx->zoom, mlx->zoom);
			ca = a;
			cb = b;
			i = 0;
			while (i < mlx->iter)
			{
				aa = a * a - b * b;
				bb = 2 * a * b;
				a = aa + ca;
				b = bb + cb;
				if (fabs(aa + bb) > 16.0)
					break ;
				i++;
			}
			color = ft_map(i, 0, mlx->iter, 0, 255);
			if (i == mlx->iter)
				color = COLOR_WHITE;
			temp = ((int)(x) * mlx->bpp / 8) + ((int)(y) * mlx->line_size);
			mlx->line[temp] = color;
			mlx->line[++temp] = color >> 8;
			mlx->line[++temp] = color >> 16;
			y += 1.0;
		}
		x += 1.0;
	}
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

	mlx.ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.ptr, WIDTH, HIEGHT, TITLE);
	mlx.iter = 10;
	mlx.zoom = 2.5;
	mlx.min = 0;
	mlx.max = WIDTH;
	image_put(&mlx);
	mlx_hook(mlx.win, 4, 0, mouse_press, &mlx);
	mlx_hook(mlx.win, 2, 0, key_parce, &mlx);
	mlx_hook(mlx.win, 17, 0, close, &mlx);
	mlx_loop(mlx.ptr);
}

int		main(void)
{
	draw();
	return (0);
}