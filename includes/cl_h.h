/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_h.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 13:54:54 by mburl             #+#    #+#             */
/*   Updated: 2020/02/21 18:49:43 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_H_H
# define CL_H_H

typedef	struct	s_compl
{
	double		im;
	double		re;
}				t_compl;

typedef struct	s_fractol
{
	t_compl	min;
	t_compl	max;
	t_compl	factor;
	t_compl	c;
	t_compl	z;
	t_compl	k;
	char	color;
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
	int		s;
	double	dx;
	double	dy;
	double	xmouse;
	double	ymouse;
	double	xmove;
	double	ymove;
	double	twoab;
}				t_fractol;

#endif