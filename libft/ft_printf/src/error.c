/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnidoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:03:20 by mnidoque          #+#    #+#             */
/*   Updated: 2020/03/06 13:49:55 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Malloc error output
*/

void	malloc_error(void)
{
	ft_putstr_fd("error: Malloc failed\n", 2);
	exit(EXIT_FAILURE);
}

/*
** Combination error output
*/

void	combi_error(void)
{
	ft_putstr_fd("error: Combination is not allowed\n", 2);
	exit(EXIT_FAILURE);
}
