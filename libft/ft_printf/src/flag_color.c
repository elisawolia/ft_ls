/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnidoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:03:20 by mnidoque          #+#    #+#             */
/*   Updated: 2020/03/06 13:18:43 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		paint(t_env *env, char *color, char *color_id)
{
	const char	*str;
	int			len;
	int			i;

	i = 0;
	str = &env->str[env->count];
	len = ft_strlen(color);
	if (ft_memcmp(str, color, len) == 0)
	{
		while (color_id[i])
		{
			to_buff_char(color_id[i], env);
			i++;
		}
		env->count += len;
		return (1);
	}
	return (0);
}

void	flag_color(t_env *env)
{
	if (paint(env, "{red}", "\033[0;31m") ||
		paint(env, "{green}", "\033[0;32m") ||
		paint(env, "{brown}", "\033[0;33m") ||
		paint(env, "{yellow}", "\033[1;33m") ||
		paint(env, "{blue}", "\033[0;34m") ||
		paint(env, "{purple}", "\033[0;35m") ||
		paint(env, "{cyan}", "\033[0;36m") ||
		paint(env, "{eoc}", "\033[0m"))
		;
	else
	{
		to_buff_char('{', env);
		env->count++;
	}
}
