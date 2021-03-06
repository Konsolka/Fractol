/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtab_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 11:42:55 by mburl             #+#    #+#             */
/*   Updated: 2020/01/23 14:44:41 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strtab_free(char **strtab)
{
	int		i;

	i = -1;
	while (strtab[++i] != NULL)
		free(strtab[i]);
	free(strtab);
}
