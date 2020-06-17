/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:54:07 by rlintill          #+#    #+#             */
/*   Updated: 2020/02/13 14:05:00 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flag_s(t_env *env, va_list args)
{
	char	*next_arg;
	int		arg_size;
	char	*precise_str;

	next_arg = va_arg(args, char *);
	if (!next_arg)
		next_arg = "(null)";
	arg_size = ft_strlen(next_arg);
	if (env->precision < arg_size && env->is_precision == 1)
	{
		env->offset -= env->precision;
		if (!(precise_str = ft_memalloc(sizeof(char) * env->precision + 1)))
			malloc_error();
		ft_memcpy(precise_str, next_arg, env->precision);
	}
	else
	{
		env->offset -= arg_size;
		precise_str = ft_strdup(next_arg);
	}
	if (!env->minus)
		to_buff_offset(env);
	to_buff_str(precise_str, env);
	if (env->minus)
		to_buff_offset(env);
}
