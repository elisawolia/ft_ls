/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/25/13 13:58:41 by rlintill          #+#    #+#             */
/*   Updated: 2020/25/13 16:29:37 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/acl.h>
#include <sys/stat.h>
#include <sys/xattr.h>

void	print_m(t_dir *dir, uint16_t color)
{
	t_file			*tmp;
	struct winsize	w;
	int				w_width;

	tmp = dir->files;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	w_width = w.ws_col;
	while (tmp != NULL)
	{
		w_width = w.ws_col - (ft_strlen(tmp->file_name) + 2);
		while (w_width > 0 && tmp != NULL)
		{
			print_filename(color, "%s", tmp);
			if (tmp->next != NULL)
				ft_putstr(", ");
			if (tmp->next == NULL)
				ft_putchar('\n');
			tmp = tmp->next;
			if (tmp != NULL)
				w_width -= (ft_strlen(tmp->file_name) + 2);
		}
		if (tmp != NULL)
			ft_putchar('\n');
	}
}

void	tabs(t_file *tmp, int max_name, int num, int to_step)
{
	int col;
	int col_last;

	col = (long long int)ft_strlen(tmp->file_name);
	col_last = col;
	while (((col = col_last + 8) & ~7) <= ((max_name + 8) & ~7))
	{
		if (tmp->next == NULL || (num > to_step))
			break ;
		ft_putchar('\t');
		col_last = col;
	}
}

void	print_list(t_dir *dir, uint16_t color)
{
	int		rows;
	int		i;
	int		j;
	t_file	*tmp;

	rows = rows_print(dir);
	i = 0;
	j = 0;
	while (i < rows)
	{
		j = 0;
		tmp = dir->files;
		while (tmp != NULL)
		{
			if (j % rows == i)
			{
				print_filename(color, "%s", tmp);
				tabs(tmp, dir->max_name, i + j, count_files(dir->files) - rows);
			}
			j++;
			tmp = tmp->next;
		}
		ft_putchar('\n');
		i++;
	}
}

void	print_one(t_dir *dir, uint16_t color)
{
	t_file *tmp;

	tmp = dir->files;
	while (tmp != NULL)
	{
		print_filename(color, "%s\n", tmp);
		tmp = tmp->next;
	}
}

void	print_d(t_opt *opt, t_dir *dir)
{
	t_file	*files;
	t_dir	*tmp;

	tmp = dir;
	files = NULL;
	while (tmp != NULL)
	{
		file_add(&(files), tmp->files);
		tmp = tmp->mult;
	}
	dir->files = files;
	merge_sort(&(dir->files), &def_sort);
	if (opt->t)
		merge_sort(&(dir->files), &time_sort);
	if (opt->s)
		merge_sort(&(dir->files), &size_sort);
	if (opt->r)
		reverse(&(dir->files));
	if (opt->l == 1)
		print_list_l(dir, opt->g);
	else if (opt->one == 1)
		print_one(dir, opt->g);
	else
		print_list(dir, opt->g);
}
