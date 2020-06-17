/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:03:20 by rlintill          #+#    #+#             */
/*   Updated: 2020/03/06 13:49:55 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pow_help(int *bits, int bit)
{
	bits[0] = bit;
	bits[1] = bit;
	bits[2] = bit;
}

static void	pow_help_free(int **num1, int **bits, int **num2)
{
	free(*num1);
	free(*num2);
	free(*bits);
}

/*
** exponentiate number
*/

static int	*power(int num, int pow, int *bit)
{
	int *num1;
	int *num2;
	int *res;
	int *bits;

	bits = new_arr(bit[1], 3);
	pow_help(bits, bit[1]);
	num1 = new_arr(num, bits[0]);
	num2 = new_arr(num, bits[1]);
	res = (pow == 0 ? new_arr(1, bits[2]) : new_arr(0, bits[2]));
	while (pow-- > 1)
	{
		if (res[10] == 0)
		{
			free(res);
			res = new_arr(0, bits[2]);
		}
		else
			wider_arr(&res, &num1, bits);
		mult_by_column(num1, num2, res, bits);
		copy_int(num1, res, bits[0], bits[2]);
	}
	bit[1] = bits[2];
	pow_help_free(&num1, &bits, &num2);
	return (res);
}

int			*prec(int *num, int prec, t_fenv *fenv)
{
	int *res;
	int buf;
	int tmp;
	int i;

	if (fenv->compos + prec >= fenv->res_bit)
		return (num);
	if (num[fenv->compos + prec] < 5)
		return (num);
	res = new_arr(0, fenv->res_bit + 1);
	copy_int(res, num, fenv->res_bit + 1, fenv->res_bit);
	i = fenv->compos + prec;
	tmp = (res[i] + 1) % 10;
	buf = (res[i] + 1) / 10;
	res[i--] = tmp;
	while (i >= 0)
	{
		tmp = (res[i] + buf) % 10;
		buf = (res[i] + buf) / 10;
		res[i--] = tmp;
	}
	free(num);
	if (cut_num(&res, fenv->res_bit + 1) == fenv->res_bit + 1)
		fenv->compos++;
	return (res);
}

int			*calc_res(unsigned long long int mant, t_fenv *fenv, int long_ch)
{
	int		*res;
	int		*arr;
	int		*n;
	int		bit;

	n = NULL;
	arr = new_arr((unsigned long long int)mant, fenv->bit);
	bit = fenv->bit;
	if (fenv->mant_num - fenv->exp_res - long_ch >= 0)
		n = power(5, fenv->mant_num - fenv->exp_res - long_ch, fenv->bits);
	else
		n = power(2, fenv->exp_res - fenv->mant_num + long_ch, fenv->bits);
	fenv->bit = bit;
	fenv->bits[2] = fenv->bits[0] + fenv->bits[1];
	res = new_arr((unsigned long long int)0, fenv->bits[2]);
	mult_by_column(arr, n, res, fenv->bits);
	fenv->bits[2] = cut_num(&res, fenv->bits[2]);
	fenv->res_bit = fenv->bits[2];
	free(arr);
	free(n);
	return (res);
}
