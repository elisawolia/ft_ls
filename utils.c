/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 13:58:41 by rlintill          #+#    #+#             */
/*   Updated: 2020/03/13 16:29:37 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		count_max(long long n)
{
	int i;

	i = 1;
	while (n > 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

int		ft_findedot(char *name)
{
	int i;

	i = ft_strlen(name);
	if (name[i - 1] == '.' && (name[i - 2] == '/' || (name[i - 2] == '.' && name[i - 3] == '/')))
		return (0);
	return (1);
}