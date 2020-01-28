/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 16:34:04 by mburl             #+#    #+#             */
/*   Updated: 2020/01/28 15:23:06 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIS_H

# define VIS_H

# define MAX_SOURCE_SIZE (0x100000)
# define HIEGHT 1000
# define WIDTH 1000
# define TITLE "Fract'ol by mburl"
# define COLOR_WHITE		0xFFFFFF
# define COLOR_RED			0xFF0000
# define COLOR_AL_RED		0xFFA500
# define COLOR_BLUE			0x0000FF
# define COLOR_AL_BLUE		0x00FFFF
# define COLOR_OLIVE		0xC0C0C0
# define COLOR_AL_GRAY		0x505050
# define COLOR_BLACK		0x000000
# define COLOR_YELLOW		0xFFFF00

typedef	struct	s_mlx
{
	void				*ptr;
	void				*win;
	void				*img;
	int					bpp;
	int					line_size;
	int					ed;
	char				*line;
	int					iter;
	double				xmin;
	double				ymin;
	double				xmax;
	double				ymax;
	double				xmouse;
	double				ymouse;
	double				zoom;
	double				xmove;
	double				ymove;
	char				test;
	double				x;
	double				y;
	double				dx;
	double				dy;
	int					i;
	int					j;
	double				aa;
	double				bb;
	double				a;
	double				b;
	double				ca;
	double				cb;
	double				twoab;
	int long			*data;

}				t_mlx;

void	image_put(t_mlx *mlx);
int		key_parce(int key, void *param);
int		mouse_move(int x, int y, void *param);
int		mouse_release(int button, int x, int y, void *param);
int		mouse_move_void(int x, int y, void *param);
int		mouse_press(int button, int x, int y, void *param);
int		win_close(void *param);
#endif