/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 11:27:02 by mburl             #+#    #+#             */
/*   Updated: 2020/02/19 17:00:51 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "visual.h"
#include "cl_h.h"
#include "libft.h"

void		terminate(char *string, cl_int ret)
{
	char	*err_num;

	err_num = NULL;
	if (ret == CL_SUCCESS)
	{
		ft_putstr(string);
		ft_putstr(" SUCCESS\n");
		return ;
	}
	err_num = ft_itoa(ret);
	err_num = ft_strjoin(" ", err_num);
	ft_putstr("ERROR in ");
	ft_putstr(string);
	ft_putchar('\n');
	ft_putstr(err_num);
	ft_strdel(&err_num);
	if (ret != CL_SUCCESS)
		exit(-1);
}