/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffun.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnidoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:03:20 by mnidoque          #+#    #+#             */
/*   Updated: 2020/02/13 15:12:45 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	to_buff_offset(t_env *env)
{
	char	*offset;

	if (env->offset > 0)
	{
		if (!(offset = ft_memalloc(sizeof(char) * env->offset + 1)))
			malloc_error();
		if (env->zero == 1)
			ft_memset(offset, '0', env->offset);
		else
			ft_memset(offset, ' ', env->offset);
		to_buff_str(offset, env);
	}
}

/*
**  move string line to buffer
*/

void	to_buff_str(char *str, t_env *env)
{
	char *temp;

	temp = env->buf;
	env->buf = ft_strjoin(env->buf, str);
	ft_memdel((void*)&temp);
	ft_memdel((void*)&str);
}

/*
**  move 1 char from line to buffer
*/

void	to_buff_char(char c, t_env *env)
{
	char	*str_c;

	if (!(str_c = ft_memalloc(sizeof(char) * 2)))
		malloc_error();
	str_c[0] = c;
	str_c[1] = '\0';
	to_buff_str(str_c, env);
}

/*
**  move line before % to buffer
*/

void	to_buff_block(t_env *env)
{
	env->first_char_pos = env->count;
	while (env->str[env->count] && env->str[env->count] != '%')
	{
		if (env->str[env->count] == '{')
			flag_color(env);
		else
		{
			to_buff_char(env->str[env->count], env);
			env->count++;
			env->res++;
		}
	}
	if (env->str[env->count] == '%')
		env->percent_pos = env->count;
}
