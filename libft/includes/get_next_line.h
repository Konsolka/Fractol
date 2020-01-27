/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 14:44:15 by mburl             #+#    #+#             */
/*   Updated: 2020/01/23 14:45:27 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H
# define BUFF_SIZE 4096

typedef struct	s_gnl
{
	char	*buf;
	int		count;
	int		i;
	int		nl;
	int		fd;
}				t_gnl;

int				get_next_line(int const fd, char **line);

#endif
