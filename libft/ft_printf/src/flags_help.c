/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:46:09 by rlintill          #+#    #+#             */
/*   Updated: 2020/03/06 14:11:57 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** set base of number
*/

void			set_base(t_env *env)
{
	if (env->str[env->count] == 'u' || env->str[env->count] == 'U'
			|| env->str[env->count] == 'd' || env->str[env->count] == 'D'
			|| env->str[env->count] == 'i')
		env->base = 10;
	if (env->str[env->count] == 'X' || env->str[env->count] == 'x'
			|| env->str[env->count] == 'p')
		env->base = 16;
	if (env->str[env->count] == 'o' || env->str[env->count] == 'O')
		env->base = 8;
}

/*
** number of digit in final base
*/

void			set_nb_digit(t_env *env)
{
	int			nb_digit;
	uintmax_t	nbr_cp;

	nbr_cp = env->cont;
	nb_digit = 0;
	if ((intmax_t)nbr_cp < 0 && (env->str[env->count] == 'd'
		|| env->str[env->count] == 'i'))
		nbr_cp = -nbr_cp;
	if ((intmax_t)nbr_cp == 0)
		env->nb_digit = 1;
	else
		while (nbr_cp /= env->base)
			nb_digit++;
	nb_digit -= (env->cont == 0) && (env->precision == 0)
		&& (env->is_precision == 1) && (env->str[env->count] != 'x')
		&& (env->str[env->count] != 'X') && (env->str[env->count] != 'o')
		&& ((env->str[env->count] != 'O') ? 1 : 0);
	env->nb_digit = nb_digit + 1;
}
