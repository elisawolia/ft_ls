/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:54:07 by rlintill          #+#    #+#             */
/*   Updated: 2020/02/13 14:05:00 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flag_c(t_env *env)
{
	env->offset--;
	if (!env->minus)
		to_buff_offset(env);
	if (!env->cont)
	{
		env->count_2 += ft_strlen(env->buf) + 1;
		to_buff_char('\0', env);
		write(env->fd, env->buf, ft_strlen(env->buf) + 1);
		free(env->buf);
		env->buf = ft_memalloc(sizeof(char));
	}
	to_buff_char(env->cont, env);
	if (env->minus)
		to_buff_offset(env);
}

void	flag_per(t_env *env)
{
	env->offset--;
	if (!env->minus)
		to_buff_offset(env);
	to_buff_char('%', env);
	if (env->minus)
		to_buff_offset(env);
}
