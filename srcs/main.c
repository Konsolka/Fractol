/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:52:57 by mburl             #+#    #+#             */
/*   Updated: 2020/01/28 11:21:35 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <mlx.h>
#include "libft.h"
#include "visual.h"
#include "key_code.h"

int		mouse_move_void(int x, int y, void *param)
{
	(void)(param);
	(void)(x);
	(void)(y);
	return (0);
}

int		mouse_release(int button, int x, int y, void *param)
{
	t_mlx	*mlx;

	if (button == MOUSE_LEFT_BUTTON)
	{
		mlx = (t_mlx *)param;
		mlx->xmouse = x;
		mlx->ymouse = y;
		image_put(mlx);
		mlx_hook(mlx->win, 6, 0, mouse_move_void, mlx);
	}
	return (0);
}

int		mouse_move(int x, int y, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	mlx->xmouse = x;
	mlx->ymouse = y;
	image_put(mlx);
	return (0);
}

int		mouse_press(int button, int x, int y, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	printf("x = %d | y = %d\nmap_x = %f | map_y = %f\n", x, y, ft_map(x, 0, WIDTH, -0.1, 0.1), ft_map(y, 0, HIEGHT, -0.1, 0.1));
	if (button == MOUSE_SCROLL_DOWN)
	{
		mlx->zoom += 0.1;
		mlx->xmove += ft_map(x, 0, WIDTH, -0.1, 0.1);
		mlx->ymove += ft_map(y, 0, HIEGHT, -0.1, 0.1);
	}
	else if (button == MOUSE_SCROLL_UP)
	{
		mlx->zoom -= 0.1;
		mlx->xmove -= ft_map(x, 0, WIDTH, -0.1, 0.1);
		mlx->ymove -= ft_map(y, 0, HIEGHT, -0.1, 0.1);
	}
	else if (button == MOUSE_LEFT_BUTTON)
		mlx_hook(mlx->win, 6, 0, mouse_move, mlx);
	image_put(mlx);
	return (0);
}

int		key_parce(int key, void *param)
{
	t_mlx	*mlx;

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
	else if (key == 15)
	{
		mlx->xmove = 0;
		mlx->ymove = 0;
		mlx->zoom = 1;
		mlx->iter = 10;
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
	double		w;
	double		h;
	double		dx;
	double		dy;
	int			j;
	int			i;
	int			iter;
	double		twoab;

	mlx->img = mlx_new_image(mlx->ptr, WIDTH, HIEGHT);
	mlx->line = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_size, &mlx->ed);
	w = 3;
	h = (w * HIEGHT) / WIDTH;
	mlx->xmin = -w / 2;
	mlx->ymin = -h / 2;
	mlx->xmax = mlx->xmin + w;
	mlx->ymax = mlx->ymin + h;
	
	// dx = (mlx->xmax - mlx->xmin) / WIDTH;
	// dy = (mlx->ymax - mlx->ymin) / HIEGHT;
	// ca = ft_map(mlx->xmouse, 0, WIDTH, -1, 1);
	// cb = ft_map(mlx->ymouse, 0, HIEGHT, -1, 1);
	// y = mlx->ymin;

	dx = 1.0;
	dy = 1.0;
	y = 0;
	
	j = 0;
	while (j < HIEGHT)
	{
		// x = mlx->xmin;
		x = 0;
		i = 0;
		while (i < WIDTH)
		{
			a = (ft_map(x, 0, WIDTH, mlx->xmin, mlx->xmax) + mlx->xmove) / mlx->zoom;
			b = (ft_map(y, 0, HIEGHT, mlx->ymin, mlx->ymax) + mlx->ymove)/ mlx->zoom;
			ca = a;
			cb = b;

			// a = x;
			// b = y;
			iter = 0;
			while (iter < mlx->iter)
			{
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
			temp = ((int)(i) * mlx->bpp / 8) + ((int)(j) * mlx->line_size);
			mlx->line[temp] = color;
			mlx->line[++temp] = color >> 8;
			mlx->line[++temp] = color >> 16;
			x += dx;
			i++;
			}
		j++;
		y += dy;
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
	mlx.xmouse = 200;
	mlx.zoom = 1;
	mlx.ymouse = 200;
	mlx.xmove = 0;
	mlx.ymove = 0;
	image_put(&mlx);
	mlx_hook(mlx.win, 4, 0, mouse_press, &mlx);
	mlx_hook(mlx.win, 2, 0, key_parce, &mlx);
	mlx_hook(mlx.win, 5, 0, mouse_release, &mlx);
	mlx_hook(mlx.win, 17, 0, close, &mlx);
	mlx_loop(mlx.ptr);
}

int		main(void)
{
	draw();
	return (0);
}