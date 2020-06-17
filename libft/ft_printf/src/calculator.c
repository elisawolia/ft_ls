/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnidoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 15:03:20 by mnidoque          #+#    #+#             */
/*   Updated: 2020/04/13 15:12:45 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**  multiplication by a column
*/

int		cut_num(int **num, int bit)
{
	int i;
	int k;
	int j;
	int *tmp;

	i = 0;
	tmp = new_arr(0, bit);
	copy_int(tmp, *num, bit, bit);
	while ((*num)[i] == 0 && i < bit)
		i++;
	free(*num);
	k = bit - i;
	*num = new_arr(0, k);
	j = 0;
	while (i < bit && j < k)
	{
		(*num)[j] = tmp[i];
		i++;
		j++;
	}
	free(tmp);
	return (k);
}

/*
**  multiplication by a column
*/

void	mult_by_column(int *num1, int *num2, int *rez, int *bit)
{
	int i;
	int j;
	int k;
	int f;
	int buf;

	i = bit[1];
	buf = 0;
	f = bit[2] - 1;
	while (i-- >= 0)
	{
		j = bit[0];
		k = f;
		while (j-- >= 0 && k >= 0)
		{
			rez[k] += buf;
			if (j >= 0 && i >= 0)
				rez[k] += (num1[j] * num2[i]);
			buf = rez[k] / 10;
			rez[k] = rez[k] % 10;
			k -= 1;
		}
		f--;
	}
}
