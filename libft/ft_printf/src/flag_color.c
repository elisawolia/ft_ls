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

static int	check_color(t_env *env)
{
	if (paint(env, "{BLACK}", "\033[0;30m") ||
		paint(env, "{RED}", "\033[0;31m") ||
		paint(env, "{GREEN}", "\033[0;32m") ||
		paint(env, "{YELLOW}", "\033[0;33m") ||
		paint(env, "{BLUE}", "\033[0;34m") ||
		paint(env, "{MAGENTA}", "\033[0;35m") ||
		paint(env, "{CYAN}", "\033[0;36m") ||
		paint(env, "{WHITE}", "\033[0;37m") ||
		paint(env, "{BBLACK}", "\033[1;30m") ||
		paint(env, "{BRED}", "\033[1;31m") ||
		paint(env, "{BGREEN}", "\033[1;32m") ||
		paint(env, "{BYELLOW}", "\033[1;33m") ||
		paint(env, "{BBLUE}", "\033[1;34m") ||
		paint(env, "{BMAGENTA}", "\033[1;35m") ||
		paint(env, "{BCYAN}", "\033[1;36m") ||
		paint(env, "{BWHITE}", "\033[1;37m") ||
		paint(env, "{EOC}", "\033[0m"))
		return (1);
	else
		return (0);
}

static int	check_formating(t_env *env)
{
	if (paint(env, "{UBLACK}", "\033[4;30m") ||
		paint(env, "{URED}", "\033[4;31m") ||
		paint(env, "{UGREEN}", "\033[4;32m") ||
		paint(env, "{UYELLOW}", "\033[4;33m") ||
		paint(env, "{UBLUE}", "\033[4;34m") ||
		paint(env, "{UMAGENTA}", "\033[4;35m") ||
		paint(env, "{UCYAN}", "\033[4;36m") ||
		paint(env, "{UWHITE}", "\033[4;37m") ||
		paint(env, "{BGBLACK}", "\033[40m") ||
		paint(env, "{BGRED}", "\033[41m") ||
		paint(env, "{BGGREEN}", "\033[42m") ||
		paint(env, "{BGYELLOW}", "\033[43m") ||
		paint(env, "{BGBLUE}", "\033[44m") ||
		paint(env, "{BGMAGENTA}", "\033[45m") ||
		paint(env, "{BGCYAN}", "\033[46m") ||
		paint(env, "{BGWHITE}", "\033[47m"))
		return (1);
	else
		return (0);
}

int			paint(t_env *env, char *color, char *color_id)
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

void		flag_color(t_env *env)
{
	if (check_color(env) || check_formating(env))
		;
	else
	{
		to_buff_char('{', env);
		env->count++;
	}
}
