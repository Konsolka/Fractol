/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 16:34:04 by mburl             #+#    #+#             */
/*   Updated: 2020/01/27 18:22:15 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIS_H

# define VIS_H

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
	void		*ptr;
	void		*win;
	void		*img;
	int			bpp;
	int			line_size;
	int			ed;
	char		*line;
	int			iter;
	double		zoom;
	double		min;
	double		max;
}				t_mlx;

void	image_put(t_mlx *mlx);
int		close(void *param);
#endif