/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:03:20 by rlintill          #+#    #+#             */
/*   Updated: 2020/03/06 13:49:55 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	create int array and stack each character of number to cell
*/

int		*new_arr(unsigned long long int num, int bit)
{
	int i;
	int *arr;

	i = bit - 1;
	if (!(arr = malloc(sizeof(int *) * bit)))
		malloc_error();
	if (!(arr = ft_memset(arr, 0, bit)))
		malloc_error();
	while (i >= 0)
	{
		arr[i] = num % 10;
		num /= 10;
		i--;
	}
	return (arr);
}

/*
** function copy numbers form num1 array to num2 array
*/

void	copy_int(int *num1, int *num2, int bit1, int bit2)
{
	int i;
	int j;

	i = bit1;
	j = bit2;
	while (--i >= 0 && --j >= 0)
	{
		num1[i] = num2[j];
	}
}

/*
** exponentiation of the number in the array
*/

void	wider_arr(int **res, int **num1, int *bits)
{
	int *tmp;

	free(*res);
	bits[2] = bits[2] + bits[2] / 3;
	*res = new_arr(0, bits[2]);
	tmp = new_arr(0, bits[2]);
	copy_int(tmp, *num1, bits[2], bits[0]);
	bits[0] = bits[2];
	free(*num1);
	*num1 = new_arr(0, bits[0]);
	copy_int(*num1, tmp, bits[0], bits[0]);
	free(tmp);
}

/*
** determines the size of a number
*/

int		num_size(t_env *env, t_fenv *fenv)
{
	int i;
	int k;

	i = 0;
	k = 0;
	if (fenv->compos <= 0)
		return (env->precision + 2);
	if (env->is_precision && env->precision > 0)
		k++;
	while (i < fenv->compos && i < fenv->res_bit)
	{
		k++;
		i++;
	}
	return (k + env->precision);
}

void	free_fenv(t_fenv *fenv)
{
	fenv->bit = 0;
	fenv->sign = 0;
	fenv->res_bit = 0;
	fenv->compos = 0;
	fenv->exp_num = 0;
	fenv->mant_num = 0;
	fenv->exp = 0;
	fenv->exp_res = 0;
	free(fenv->bits);
}
