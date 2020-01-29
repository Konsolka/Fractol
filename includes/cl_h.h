/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_h.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 13:54:54 by mburl             #+#    #+#             */
/*   Updated: 2020/01/29 13:50:20 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_H_H
# define CL_H_H

typedef struct	s_fractol
{
	int		iter;
	double	xmin;
	double	ymin;
	double	xmax;
	double	ymax;
	double	zoom;
	double	x;
	double	y;
	double	dx;
	double	dy;
	int		i;
	int		j;
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