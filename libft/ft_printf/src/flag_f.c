/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnidoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:03:20 by mnidoque          #+#    #+#             */
/*   Updated: 2020/03/06 13:49:55 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_fenv	*init_fenv(int bit, unsigned long int num)
{
	t_fenv	*fenv;

	if (!(fenv = ft_memalloc(sizeof(t_fenv))))
		malloc_error();
	fenv->bit = bit;
	fenv->res_bit = bit;
	fenv->exp_num = 1023;
	fenv->mant_num = 52;
	fenv->sign = num >> (bit - 1);
	fenv->exp = num << 1;
	fenv->exp = fenv->exp >> (fenv->mant_num + 1);
	fenv->exp_res = fenv->exp - (fenv->exp_num);
	fenv->compos = fenv->bit - (fenv->mant_num - fenv->exp_res);
	fenv->bits = new_arr(0, 3);
	fenv->bits[0] = fenv->bit;
	fenv->bits[1] = 2 * fenv->bit;
	fenv->bits[2] = fenv->bits[0] + fenv->bits[1];
	return (fenv);
}

static int		valid_float(t_fenv *fenv, unsigned long long int mant)
{
	if (fenv->mant_num - fenv->exp_res == -972
		&& mant == 4503599627370496 && fenv->sign == 0)
		return (1);
	else if (fenv->mant_num - fenv->exp_res == -972
		&& mant == 4503599627370496 && fenv->sign == 1)
		return (2);
	else if (fenv->mant_num - fenv->exp_res == -972 && mant == 6755399441055744)
		return (3);
	return (0);
}

void			prec_def(t_env *env)
{
	if (!env->is_precision)
	{
		env->is_precision = 1;
		env->precision = 6;
	}
}

void			flag_f(t_env *env, va_list args)
{
	t_fenv						*fenv;
	unsigned long int			*ptr;
	unsigned long long int		mant;
	double						cont;
	int							*res;

	cont = (double)va_arg(args, double);
	ptr = (unsigned long int *)&cont;
	fenv = init_fenv(64, *ptr);
	if (cont == 0)
		return (float_zero(&fenv, env));
	mant = *ptr & 4503599627370495;
	mant = mant | 4503599627370496;
	if (valid_float(fenv, mant))
		return (put_unval(&fenv, env, valid_float(fenv, mant)));
	res = calc_res(mant, fenv, 0);
	fenv->compos = fenv->res_bit - (fenv->mant_num - fenv->exp_res);
	prec_def(env);
	res = prec(res, env->precision, fenv);
	float_output(env, fenv, res);
	free_fenv(fenv);
	free(res);
	free(fenv);
}
