/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 12:38:17 by rlintill          #+#    #+#             */
/*   Updated: 2020/03/06 13:48:34 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** convert DEC to HEX and return as string
*/

char	*flag_x_help(t_env *env)
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
		if ((env->cont % 16 >= 10 || env->cont % 16 <= 15))
			res[nb_digit] = char_ref + (env->cont % 16);
		if (env->cont % 16 < 10)
			res[nb_digit] = env->cont % 16 + '0';
		env->cont /= 16;
	}
	return (res);
}

/*
** handling x and X flag with additions
*/

void	flag_x_util(t_env *env)
{
	if (env->grille && env->is_precision && env->precision == 0)
		env->zero = 0;
	if (env->grille && ((env->cont != 0) || (env->str[env->count] == 'p')))
		env->offset -= 2;
	else
		env->grille = 0;
	if (env->cont == 0 && env->precision == 0 && env->is_precision)
		env->offset++;
	env->offset -= ((env->precision > env->nb_digit) ?
			env->precision : env->nb_digit);
}

void	flag_x(t_env *env)
{
	flag_x_util(env);
	if (env->grille && env->zero && env->caps)
		to_buff_str(ft_strdup("0X"), env);
	if (env->grille && env->zero && !env->caps)
		to_buff_str(ft_strdup("0x"), env);
	if (!env->minus)
		to_buff_offset(env);
	if (env->grille && env->caps && !env->zero &&
			(env->cont || env->str[env->count] == 'p'))
		to_buff_str(ft_strdup("0X"), env);
	if (env->grille && !env->caps && !env->zero &&
			(env->cont || env->str[env->count] == 'p'))
		to_buff_str(ft_strdup("0x"), env);
	put_precision(env, env->nb_digit);
	if (!((env->cont == 0) && (env->precision == 0) && (env->is_precision)))
		to_buff_str(flag_x_help(env), env);
	if (env->minus)
		to_buff_offset(env);
}
