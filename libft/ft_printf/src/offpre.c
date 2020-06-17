/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offpre.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnidoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:03:20 by mnidoque          #+#    #+#             */
/*   Updated: 2020/02/13 14:51:54 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**  count precision
*/

void	set_precision(int init_index, t_env *env)
{
	char	*num;
	int		max;

	if (env->str[env->count] == '+' && env->str[env->count++])
		env->plus = 1;
	if (env->str[env->count] == '.' && env->str[env->count++])
		env->is_precision = 1;
	while (ft_isdigit(env->str[env->count]))
		env->count++;
	if (env->count - init_index == 0)
		return ;
	init_index += env->str[init_index] == '.' ? 1 : 0;
	if (!(num = ft_memalloc(sizeof(char) * env->count - init_index + 1)))
		malloc_error();
	max = env->count;
	env->count = init_index;
	ft_memcpy(num, &env->str[env->count], max - env->count);
	env->count = max;
	env->precision = ft_atoi(num);
	if (env->precision == 0 || env->dot == 1)
		env->is_precision = 1;
	ft_memdel((void*)&num);
}

/*
**  count offset
*/

void	set_offset(int init_index, t_env *env)
{
	char	*num;
	int		i;
	int		max;

	i = 0;
	if (env->str[env->count] == '0' && !env->minus)
	{
		env->count++;
		return ;
	}
	while (ft_isdigit(env->str[env->count]))
		env->count++;
	if (!(num = ft_memalloc(sizeof(char) * env->count - init_index + 1)))
		malloc_error();
	max = env->count;
	env->count = init_index;
	while (env->count < max)
		num[i++] = env->str[env->count++];
	num[i] = '\0';
	env->offset = ft_atoi(num);
	ft_memdel((void*)&num);
}
