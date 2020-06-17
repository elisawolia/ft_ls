/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:03:20 by rlintill          #+#    #+#             */
/*   Updated: 2020/03/06 13:49:55 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	move float number to buffer from int array
*/

static void	to_buff_float_help(t_env *env, t_fenv *fenv, int *num)
{
	int i;
	int diff;

	i = 0;
	while (i < fenv->res_bit && i < fenv->compos + env->precision)
	{
		if (i == fenv->compos)
			to_buff_char('.', env);
		to_buff_char(num[i++] + '0', env);
	}
	diff = (fenv->res_bit > fenv->compos ?
		env->precision + fenv->compos - i : env->precision);
	if (i < fenv->compos + env->precision)
	{
		if (i <= fenv->compos && env->precision > 0)
			to_buff_char('.', env);
		i = 0;
		while (i++ < diff)
			to_buff_char('0', env);
	}
}

static void	to_buff_float(t_env *env, t_fenv *fenv, int *num)
{
	int i;
	int prec;

	i = 0;
	prec = env->precision;
	if (fenv->compos <= 0)
	{
		to_buff_char('0', env);
		if (prec != 0)
			to_buff_char('.', env);
		while ((fenv->compos)++ < 0 && prec > 0)
		{
			to_buff_char('0', env);
			prec--;
		}
		while (prec > 0 && i < fenv->res_bit)
		{
			to_buff_char(num[i++] + '0', env);
			prec--;
		}
		while (prec-- > 0)
			to_buff_char('0', env);
	}
	else
		to_buff_float_help(env, fenv, num);
}

/*
** write formatted result to buffer
*/

void		float_output(t_env *env, t_fenv *fenv, int *res)
{
	env->offset -= num_size(env, fenv);
	if (fenv->sign && env->zero)
		to_buff_char('-', env);
	env->offset -= (fenv->sign && !env->space) ? 1 : 0;
	env->offset -= (!fenv->sign && env->plus) ? 1 : 0;
	if (!env->minus && !env->zero)
		to_buff_offset(env);
	if (env->plus && !fenv->sign)
		to_buff_char('+', env);
	if (fenv->sign && !env->zero)
		to_buff_char('-', env);
	if (!fenv->sign && env->space && !env->plus)
		to_buff_char(' ', env);
	if (env->zero)
		put_zero(env);
	to_buff_float(env, fenv, res);
	if (env->precision == 0 && env->grille)
		to_buff_char('.', env);
	env->offset -= (env->precision == 0 && env->grille) ? 1 : 0;
	if (env->minus)
		to_buff_offset(env);
}

void		float_zero(t_fenv **fenv, t_env *env)
{
	int *res;
	int i;

	i = 0;
	if (!env->is_precision)
	{
		env->is_precision = 1;
		env->precision = 6;
	}
	if (!(res = (int*)malloc(sizeof(int*) * env->precision)))
		return ;
	while (i < env->precision)
	{
		res[i] = 0;
		i++;
	}
	(*fenv)->compos = -1;
	float_output(env, *fenv, res);
	free_fenv(*fenv);
	free(*fenv);
}

void		put_unval(t_fenv **fenv, t_env *env, int error)
{
	char	*str;

	str = NULL;
	if (error == 1)
		str = ft_strdup("inf");
	else
		str = (error == 2 ? ft_strdup("-inf") : ft_strdup("nan"));
	env->offset -= 3;
	env->offset += (env->space && error != 2) ? 1 : 0;
	env->offset -= (error == 2 && !env->space) ? 1 : 0;
	env->offset -= (error == 1 && env->plus) ? 1 : 0;
	env->zero = 0;
	if (!env->minus)
		to_buff_offset(env);
	if (env->plus && error == 1)
		to_buff_char('+', env);
	to_buff_str(str, env);
	if (env->minus)
		to_buff_offset(env);
	free_fenv(*fenv);
	free(*fenv);
}
