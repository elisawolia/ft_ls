/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnidoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:03:20 by mnidoque          #+#    #+#             */
/*   Updated: 2020/03/06 13:46:01 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	length_flags_h_hh(t_env *env, va_list args)
{
	env->count++;
	if (env->str[env->count] == 'd' || env->str[env->count] == 'i')
		env->cont = (short int)va_arg(args, uintmax_t);
	else if (env->str[env->count] == 'u' || env->str[env->count] == 'o' ||
			env->str[env->count] == 'x' || env->str[env->count] == 'X')
		env->cont = (unsigned short int)va_arg(args, uintmax_t);
	while (env->str[env->count] == 'h')
	{
		env->count++;
		if (env->str[env->count] == 'd' || env->str[env->count] == 'i')
			env->cont = (signed char)va_arg(args, uintmax_t);
		else if (env->str[env->count] == 'o' || env->str[env->count] == 'u' ||
				env->str[env->count] == 'x' || env->str[env->count] == 'X')
			env->cont = (unsigned char)va_arg(args, uintmax_t);
	}
	if (env->str[env->count] == 'p')
		env->cont = (unsigned long long int)va_arg(args, uintmax_t);
	else if (env->str[env->count] == 'c' || env->str[env->count] == 'C')
	{
		env->cont = (wchar_t)va_arg(args, uintmax_t);
		env->is_unicode = 1;
	}
}

static void	length_flags_l_ll(t_env *env, va_list args)
{
	env->count++;
	if (env->str[env->count] == 'd' || env->str[env->count] == 'i')
		env->cont = (long int)va_arg(args, uintmax_t);
	else if (env->str[env->count] == 'u' || env->str[env->count] == 'o' ||
			env->str[env->count] == 'x' || env->str[env->count] == 'X')
		env->cont = (unsigned long int)va_arg(args, uintmax_t);
	while (env->str[env->count] == 'l')
	{
		env->count++;
		if (env->str[env->count] == 'd' || env->str[env->count] == 'i')
			env->cont = (long long int)va_arg(args, uintmax_t);
		else if (env->str[env->count] == 'o' || env->str[env->count] == 'u' ||
				env->str[env->count] == 'x' || env->str[env->count] == 'X')
			env->cont = (unsigned long long int)va_arg(args, uintmax_t);
	}
	if (env->str[env->count] == 'p')
		env->cont = (unsigned long long int)va_arg(args, uintmax_t);
	else if (env->str[env->count] == 'c' || env->str[env->count] == 'C')
	{
		env->cont = (wchar_t)va_arg(args, uintmax_t);
		env->is_unicode = 1;
	}
	else if (env->str[env->count] == 's')
		env->is_unicode = 1;
}

static void	length_flags_z_j(t_env *env, va_list args)
{
	while (env->str[env->count] == 'z' || env->str[env->count] == 'j')
		env->count++;
	if (env->str[env->count - 1] == 'z')
	{
		if (env->str[env->count] == 'd' || env->str[env->count] == 'i' ||
			env->str[env->count] == 'u' || env->str[env->count] == 'o' ||
			env->str[env->count] == 'x' || env->str[env->count] == 'X')
			env->cont = (size_t)va_arg(args, uintmax_t);
	}
	else
	{
		if (env->str[env->count] == 'd' || env->str[env->count] == 'i')
			env->cont = (intmax_t)va_arg(args, uintmax_t);
		else if (env->str[env->count] == 'u' || env->str[env->count] == 'o' ||
				env->str[env->count] == 'x' || env->str[env->count] == 'X')
			env->cont = (uintmax_t)va_arg(args, uintmax_t);
	}
	if (env->str[env->count] == 'p')
		env->cont = (unsigned long long int)va_arg(args, uintmax_t);
	else if (env->str[env->count] == 'c' || env->str[env->count] == 'C')
	{
		env->cont = (wchar_t)va_arg(args, uintmax_t);
		env->is_unicode = 1;
	}
}

static void	length_flags_d_u_o(t_env *env, va_list args)
{
	int	temp_count;

	temp_count = env->count;
	while ((env->str[temp_count] == 'h') || (env->str[temp_count] == 'l')
			|| (env->str[temp_count] == 'j') || (env->str[temp_count] == 'z'))
		temp_count++;
	if ((env->str[temp_count] == 'D') || (env->str[temp_count] == 'U')
			|| (env->str[temp_count] == 'O'))
		env->count = temp_count;
	if (env->str[env->count] == 'D')
		env->cont = (long int)va_arg(args, uintmax_t);
	else if (env->str[env->count] == 'U' || env->str[env->count] == 'O')
		env->cont = (unsigned long int)va_arg(args, uintmax_t);
}

void		length_flags(t_env *env, va_list args)
{
	length_flags_d_u_o(env, args);
	if (env->str[env->count] == 'C')
		env->cont = (wchar_t)va_arg(args, uintmax_t);
	else if ((env->str[env->count] == 'd') || (env->str[env->count] == 'i'))
		env->cont = (int)va_arg(args, uintmax_t);
	else if (env->str[env->count] == 'p')
		env->cont = (unsigned long long int)va_arg(args, uintmax_t);
	else if (env->str[env->count] == 'c')
		env->cont = (unsigned char)va_arg(args, uintmax_t);
	else if ((env->str[env->count] == 'u') || (env->str[env->count] == 'o')
			|| (env->str[env->count] == 'X') || (env->str[env->count] == 'x'))
		env->cont = (unsigned int)va_arg(args, uintmax_t);
	else if (env->str[env->count] == 'h')
		length_flags_h_hh(env, args);
	else if (env->str[env->count] == 'l')
		length_flags_l_ll(env, args);
	else if ((env->str[env->count] == 'z') || (env->str[env->count] == 'j'))
		length_flags_z_j(env, args);
}
