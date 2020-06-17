/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:46:09 by rlintill          #+#    #+#             */
/*   Updated: 2020/03/06 14:11:57 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** manage num flags
*/

static void		num_flags(t_env *env)
{
	env->zero = env->precision != 0 ? 0 : env->zero;
	set_base(env);
	set_nb_digit(env);
	env->caps = env->str[env->count] == 'X' ? 1 : 0;
	env->grille = env->str[env->count] == 'p' ? 1 : env->grille;
	if ((env->str[env->count] == 'X' || env->str[env->count] == 'x')
			&& env->grille == 1)
		env->grille = 2;
	if (env->str[env->count] == 'u' || env->str[env->count] == 'U'
			|| env->str[env->count] == 'd' ||
			env->str[env->count] == 'D' || env->str[env->count] == 'i')
		flag_di(env);
	if (env->str[env->count] == 'X' ||
			env->str[env->count] == 'x' || env->str[env->count] == 'p')
		flag_x(env);
	if (env->str[env->count] == 'o' || env->str[env->count] == 'O')
		flag_o(env);
}

/*
**  find flag e.g. %s %c
*/

void			find_flag_continue(t_env *env, va_list args)
{
	if (env->str[env->count] == 's')
		flag_s(env, args);
	else if (env->str[env->count] == 'c')
		flag_c(env);
	else if (env->str[env->count] == '%')
		flag_per(env);
	else if (env->str[env->count] == 'f' || env->str[env->count] == 'L')
		float_flags(env, args);
	else if (env->str[env->count] == 'd' || env->str[env->count] == 'D' ||
		env->str[env->count] == 'u' || env->str[env->count] == 'U' ||
		env->str[env->count] == 'x' || env->str[env->count] == 'X' ||
		env->str[env->count] == 'o' || env->str[env->count] == 'O' ||
		env->str[env->count] == 'p' || env->str[env->count] == 'i' ||
		env->str[env->count] == 'l' || env->str[env->count] == 'h' ||
		env->str[env->count] == 'j' || env->str[env->count] == 'z')
		num_flags(env);
}

/*
**  main function of find flag
*/

void			find_flag(t_env *env, va_list args)
{
	set_def(env);
	check_preflag(env);
	if (!check_flag(env->str[env->count]))
	{
		env->count--;
		return ;
	}
	if (env->plus == 1 && env->space == 1)
		env->space = 0;
	if (env->zero == 1 && env->minus)
		env->zero = 0;
	if (env->dot == 0 || env->zero != 0)
		set_offset(env->count, env);
	set_precision(env->count, env);
	if (env->space == 1 && env->offset != 0)
		env->offset -= 1;
	else
		env->offset -= env->space;
	length_flags(env, args);
	find_flag_continue(env, args);
}

/*
**  flag validation
*/

int				check_flag(char c)
{
	if (ft_isdigit(c) || c == 's' ||
		c == 'p' || c == 'd' || c == 'D' ||
		c == 'o' || c == 'O' || c == 'u' ||
		c == 'U' || c == 'x' || c == 'X' ||
		c == 'c' || c == '.' || c == '%' ||
		c == 'h' || c == 'l' || c == 'i' ||
		c == 'j' || c == 'z' || c == 'f' || c == 'L')
		return (1);
	return (0);
}

/*
**  find and validate modifications of flag
*/

void			check_preflag(t_env *env)
{
	char c;

	c = env->str[env->count];
	while (c == '#' || c == '0' || c == '-' || c == ' ' || c == '+' || c == '.')
	{
		if (env->str[env->count] == '#')
			env->grille = 1;
		else if (env->str[env->count] == '0' && env->str[env->count + 1] != '.')
			env->zero = 1;
		else if (env->str[env->count] == '-')
			env->minus = 1;
		else if (env->str[env->count] == ' ')
			env->space = 1;
		else if (env->str[env->count] == '+')
			env->plus = 1;
		else if (env->str[env->count] == '.')
		{
			env->zero = 0;
			env->dot = 1;
			env->is_precision = 1;
			env->count++;
			break ;
		}
		c = env->str[++(env->count)];
	}
}
