/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_o.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:54:07 by rlintill          #+#    #+#             */
/*   Updated: 2020/03/06 13:44:49 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** convert DEC to OCT and return as string
*/

char	*flag_o_help(t_env *env)
{
	int				nb_digit;
	char			*res;
	int				char_ref;

	char_ref = env->caps == 1 ? 55 : 87;
	set_nb_digit(env);
	nb_digit = env->nb_digit;
	if (!(res = (char*)ft_memalloc(sizeof(char) * nb_digit + 1)))
		malloc_error();
	res[nb_digit] = '\0';
	while (nb_digit--)
	{
		if ((env->cont % 8 >= 10 || env->cont % 8 <= 15))
			res[nb_digit] = char_ref + (env->cont % 8);
		if (env->cont % 8 < 10)
			res[nb_digit] = env->cont % 8 + '0';
		env->cont /= 8;
	}
	return (res);
}

/*
** handling o and O flag with additions
*/

void	flag_o(t_env *env)
{
	int	print_zero;

	env->zero = ((env->str[env->count] == 'O' || env->str[env->count] == 'o')
		&& (env->precision == 0) && (env->is_precision == 1)) ? 0 : env->zero;
	print_zero = ((env->grille == 1) && (env->precision == 0)
			&& (env->is_precision)) ? 1 : 0;
	env->grille = ((env->grille == 1) && (env->cont == 0)
			&& (env->is_precision == 0)) ? 0 : env->grille;
	env->offset -= (env->precision > env->nb_digit) ?
		env->precision : env->nb_digit;
	env->offset -= ((env->precision > env->nb_digit) ? 0 : env->grille);
	if (env->grille && env->precision <= env->nb_digit && env->cont)
		env->precision += env->nb_digit - env->precision + 1;
	env->offset += ((env->cont == 0) && (env->precision == 0)
			&& (env->is_precision == 1)) ? 1 : 0;
	if (!env->minus)
		to_buff_offset(env);
	put_precision(env, env->nb_digit);
	if (!(!env->cont && !env->precision && env->is_precision && !print_zero))
		to_buff_str(flag_o_help(env), env);
	if (env->minus)
		to_buff_offset(env);
}
