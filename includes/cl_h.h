/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_h.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 13:54:54 by mburl             #+#    #+#             */
/*   Updated: 2020/03/04 14:19:13 by mburl            ###   ########.fr       */
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
	double	xmin;
	double	ymin;
	double	xmax;
	double	ymax;
	int		s;
	double	twoab;
}				t_fractol;

#endif
