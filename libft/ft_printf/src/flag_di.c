/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_di.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 14:37:50 by rlintill          #+#    #+#             */
/*   Updated: 2020/03/06 13:30:30 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** processing the maximum and minimum values
*/

char	*flag_di_help(t_env *env)
{
	int			nb_digit;
	char		*res;

	if ((unsigned long int)env->cont == -9223372036854775808U)
		return (ft_strdup("9223372036854775808"));
	if ((intmax_t)env->cont < 0 && env->str[env->count] != 'u'
			&& env->str[env->count] != 'U')
		env->cont = -env->cont;
	set_nb_digit(env);
	nb_digit = env->nb_digit;
	if (!(res = (char*)ft_memalloc(sizeof(char) * nb_digit + 1)))
		malloc_error();
	res[nb_digit] = '\0';
	while (nb_digit--)
	{
		res[nb_digit] = env->cont % env->base + '0';
		env->cont /= env->base;
	}
	return (res);
}

/*
** set precision of value
*/

void	put_precision(t_env *env, int arg_size)
{
	char	*prec;

	if (env->precision > arg_size)
	{
		if (!(prec = ft_memalloc(sizeof(char) * env->precision - arg_size + 1)))
			malloc_error();
		ft_memset(prec, '0', env->precision - arg_size);
		to_buff_str(prec, env);
	}
}

/*
** put 0 to buffer
*/

void	put_zero(t_env *env)
{
	char	*zero;

	if (env->offset > 0)
	{
		if (!(zero = ft_memalloc(sizeof(char) * env->offset + 1)))
			malloc_error();
		ft_memset(zero, '0', env->offset);
		to_buff_str(zero, env);
	}
	env->offset = 0;
}

/*
** handling d and i flag with additions
*/

void	flag_di_util(t_env *env)
{
	env->offset -= (env->precision > env->nb_digit) ?
		env->precision : env->nb_digit;
	env->plus = (env->str[env->count] == 'u'
			|| env->str[env->count] == 'U') ? 0 : env->plus;
	env->offset -= (env->plus && (intmax_t)env->cont >= 0) ? 1 : 0;
}

void	flag_di(t_env *env)
{
	flag_di_util(env);
	if ((intmax_t)env->cont < 0 && env->zero)
		to_buff_char('-', env);
	env->offset -= ((intmax_t)env->cont < 0 && !env->space) ? 1 : 0;
	if (!env->minus && !env->zero)
		to_buff_offset(env);
	if (env->plus && (intmax_t)env->cont >= 0)
		to_buff_char('+', env);
	if ((intmax_t)env->cont < 0 && !env->zero && env->str[env->count] != 'u' &&
			env->str[env->count] != 'U')
		to_buff_char('-', env);
	if ((env->str[env->count] == 'd'
			|| env->str[env->count] == 'i' || env->str[env->count] == 'D')
			&& (intmax_t)env->cont >= 0 && env->space && !env->plus)
		to_buff_char(' ', env);
	if (env->zero)
		put_zero(env);
	put_precision(env, env->nb_digit);
	if (!(env->cont == 0 && env->precision == 0 && env->is_precision))
		to_buff_str(flag_di_help(env), env);
	if (env->minus)
		to_buff_offset(env);
}
