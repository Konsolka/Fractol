/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 15:51:08 by mburl             #+#    #+#             */
/*   Updated: 2020/03/05 10:00:13 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_chrcmp(const char *str, const char *str2)
{
	while (*str && *str2 && *str == *str2)
	{
		str++;
		str2++;
	}
	return ((int)(*str) - (int)(*str2));
}
