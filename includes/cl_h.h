/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_h.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 13:54:54 by mburl             #+#    #+#             */
/*   Updated: 2020/02/21 14:12:11 by mburl            ###   ########.fr       */
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

#endif