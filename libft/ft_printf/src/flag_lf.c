/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_lf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnidoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:03:20 by mnidoque          #+#    #+#             */
/*   Updated: 2020/03/06 13:49:55 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** function algorithm selection
*/

void			float_flags(t_env *env, va_list args)
{
	if (env->str[env->count] == 'L' || env->str[env->count] == 'l')
	{
		env->count++;
		if (env->str[env->count] == 'l' || env->str[env->count] == 'L')
			env->count++;
		if (env->str[env->count] == 'f')
			flag_lf(env, args);
	}
	else if (env->str[env->count] == 'f')
		flag_f(env, args);
}

static t_fenv	*init_fenv_long(unsigned short *short_ptr)
{
	t_fenv					*fenv;
	unsigned long int		sig;

	if (!(fenv = ft_memalloc(sizeof(t_fenv))))
		malloc_error();
	fenv->bit = 80;
	fenv->res_bit = 80;
	fenv->exp_num = 16383;
	fenv->mant_num = 64;
	sig = *short_ptr;
	fenv->sign = sig >> 15;
	fenv->exp_res = sig & 32767;
	fenv->exp_res = fenv->exp_res - (fenv->exp_num);
	fenv->compos = fenv->res_bit - (fenv->mant_num - fenv->exp_res);
	fenv->bits = new_arr(0, 3);
	fenv->bits[0] = fenv->bit;
	fenv->bits[1] = 2 * fenv->bit;
	fenv->bits[2] = fenv->bits[0] + fenv->bits[1];
	return (fenv);
}

/*
** function of long float
*/

void			flag_lf(t_env *env, va_list args)
{
	t_fenv							*fenv;
	unsigned short					*short_ptr;
	unsigned long int				*ptr;
	long double						cont;
	int								*res;

	cont = (long double)va_arg(args, long double);
	short_ptr = (unsigned short *)&cont;
	ptr = (unsigned long int *)&cont;
	short_ptr = short_ptr + 4;
	fenv = init_fenv_long(short_ptr);
	if (cont == 0)
		return (float_zero(&fenv, env));
	res = calc_res(*ptr, fenv, 1);
	prec_def(env);
	fenv->compos = fenv->res_bit - (fenv->mant_num - 1 - fenv->exp_res);
	res = prec(res, env->precision, fenv);
	float_output(env, fenv, res);
	free_fenv(fenv);
	free(res);
	free(fenv);
}
