/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 13:58:41 by rlintill          #+#    #+#             */
/*   Updated: 2020/03/13 16:29:37 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		count_max(long long n)
{
	int i;

	i = 1;
	if (n == 0)
		return (2);
	while (n > 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

void	ft_putspace(ssize_t n)
{
	ssize_t	i;

	i = 0;
	while (i < n)
	{
		ft_putchar(' ');
		i++;
	}
}

int		ft_findedot(char *name)
{
	int	i;

	i = ft_strlen(name);
	if (name[i - 1] == '.' && (name[i - 2] == '/'
		|| (name[i - 2] == '.' && name[i - 3] == '/')))
		return (0);
	return (1);
}

int		count_files(t_file *file)
{
	int		i;
	t_file	*tmp;

	i = 0;
	tmp = file;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	lstat_error(void)
{
	perror("lstat");
	exit(1);
}

void	malloc_err(void)
{
	perror("malloc");
	exit(1);
}

ssize_t	max(ssize_t a, ssize_t b)
{
	return (a > b ? a : b);
}
