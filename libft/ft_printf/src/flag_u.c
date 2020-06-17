/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_u.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 14:37:44 by rlintill          #+#    #+#             */
/*   Updated: 2020/02/13 14:37:46 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flag_u(t_env *env, va_list args)
{
	unsigned int	num;
	char			*res;

	if (env->minus && env->zero)
		combi_error();
	num = va_arg(args, unsigned int);
	res = ft_itoa(num);
	if (env->is_precision)
	{
		if (env->precision == 0 && num == 0)
		{
			free(res);
			res = ft_strdup("");
		}
		else
			res = precision(env, res, 0);
	}
	if (env->zero && !env->is_precision)
		res = zero_offset(env, res, 0);
	else if (env->offset)
		res = space_offset(env, res, 0, 0);
	env->buf = ft_strjoin(env->buf, res);
}
