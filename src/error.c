/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 13:58:41 by rlintill          #+#    #+#             */
/*   Updated: 2020/03/13 16:29:37 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** error if lstat can't get info
*/

void	lstat_error(void)
{
	perror("lstat");
	exit(1);
}

/*
** error if program can't find file or directory
*/

void	ls_error(char *file)
{
	ft_printf_fd(2, "ls: %s: No such file or directory\n", file);
	exit(1);
}

/*
** malloc error handling
*/

void	malloc_err(void)
{
	perror("malloc");
	exit(1);
}
