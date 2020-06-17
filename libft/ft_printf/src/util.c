/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 17:19:37 by rlintill          #+#    #+#             */
/*   Updated: 2020/02/13 16:18:22 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*space_offset(t_env *env, char *res, int minus, int flag_char)
{
	char	*offset;
	int		leng;

	offset = NULL;
	leng = ft_strlen(res);
	if (flag_char)
		leng = 1;
	if (minus && !env->is_precision)
		leng++;
	if (env->offset - leng > 0)
	{
		offset = ft_memalloc((size_t)(env->offset - leng + 1));
		offset = ft_memset(offset, ' ', env->offset - leng);
		offset[env->offset - leng + 1] = '\0';
		if (!env->minus)
			res = ft_strjoin(offset, res);
		else
			res = ft_strjoin(res, offset);
		env->res += (env->offset - leng);
	}
	if (offset != NULL)
		ft_memdel((void*)&offset);
	return (res);
}

char	*zero_offset(t_env *env, char *res, int minus)
{
	char	*offset;
	int		leng;

	offset = NULL;
	leng = ft_strlen(res);
	if (minus || (env->zero && env->plus))
		leng += 1;
	if (env->offset - leng > 0)
	{
		offset = ft_memalloc((size_t)(env->offset - leng + 1));
		offset = ft_memset(offset, '0', env->offset - leng);
		offset[env->offset - leng + 1] = '\0';
		if (!env->minus)
			res = ft_strjoin(offset, res);
		env->res += (env->offset - leng);
	}
	if (minus)
	{
		res = ft_strjoin("-", res);
		env->res++;
	}
	if (offset != NULL)
		ft_memdel((void*)&offset);
	return (res);
}

char	*precision(t_env *env, char *res, int minus)
{
	char	*offset;
	int		leng;

	offset = NULL;
	leng = ft_strlen(res);
	if (env->precision - leng > 0)
	{
		offset = ft_memalloc((size_t)(env->precision - leng + 1));
		offset = ft_memset(offset, '0', env->precision - leng);
		offset[env->precision - leng + 1] = '\0';
		res = ft_strjoin(offset, res);
		env->res += (env->precision - leng);
	}
	if (minus)
	{
		res = ft_strjoin("-", res);
		env->res++;
	}
	if (offset != NULL)
		ft_memdel((void*)&offset);
	return (res);
}

void	plus_minus(t_env *env, char **res, int minus, int num)
{
	if (!minus && env->plus && num >= 0)
	{
		*res = ft_strjoin("+", *res);
		env->res++;
	}
}

void	space(t_env *env, char **res, int minus)
{
	if (env->space && !minus)
	{
		*res = ft_strjoin(" ", *res);
		env->res++;
	}
}
