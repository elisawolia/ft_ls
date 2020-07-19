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

void	print_m(t_dir *dir)
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
			ft_printf("%s", tmp->file_name);
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

void	print_type(unsigned long mode)
{
	if (S_ISBLK(mode))
		ft_putchar('b');
	else if (S_ISCHR(mode))
		ft_putchar('c');
	else if (S_ISFIFO(mode))
		ft_putchar('f');
	else if (S_ISREG(mode))
		ft_putchar('-');
	else if (S_ISDIR(mode))
		ft_putchar('d');
	else if (S_ISLNK(mode))
		ft_putchar('l');
	else
		ft_putchar('s');
}

void	print_rights(unsigned long mode)
{
	(S_IRUSR & mode) ? ft_putchar('r') : ft_putchar('-');
	(S_IWUSR & mode) ? ft_putchar('w') : ft_putchar('-');
	if (S_ISUID & mode)
		(S_IXUSR & mode) ? ft_putchar('s') : ft_putchar('S');
	else
		(S_IXUSR & mode) ? ft_putchar('x') : ft_putchar('-');
	(S_IRGRP & mode) ? ft_putchar('r') : ft_putchar('-');
	(S_IWGRP & mode) ? ft_putchar('w') : ft_putchar('-');
	if (S_ISGID & mode)
		(S_IXUSR & mode) ? ft_putchar('s') : ft_putchar('S');
	else
		(S_IXGRP & mode) ? ft_putchar('x') : ft_putchar('-');
	(S_IROTH & mode) ? ft_putchar('r') : ft_putchar('-');
	(S_IWOTH & mode) ? ft_putchar('w') : ft_putchar('-');
	if (S_ISVTX & mode)
		(S_IXUSR & mode) ? ft_putchar('t') : ft_putchar('T');
	else
		(S_IXOTH & mode) ? ft_putchar('x') : ft_putchar('-');
	ft_putchar(' ');
}

void	print_list_l(t_dir *dir)
{
	t_file *tmp;

	tmp = dir->files;
	while (tmp != NULL)
	{
		print_type(tmp->mode);
		print_rights(tmp->mode);
		ft_putspace((dir->max_link + 1) -
			(long long int)(count_max(tmp->link)));
		ft_printf("%ld %s", tmp->link, getpwuid(tmp->uid)->pw_name);
		ft_putspace((dir->max_uid + 1) -
			(long int)ft_strlen(getpwuid(tmp->uid)->pw_name));
		ft_putspace((dir->max_gid + 1) -
			(long int)ft_strlen(getgrgid(tmp->gid)->gr_name));
		ft_printf("%s ", getgrgid(tmp->gid)->gr_name);
		ft_putspace((dir->max_size + 1) -
			(long long int)(count_max(tmp->size)));
		ft_printf("%d ", tmp->size);
		ft_printf("%.12s ", ctime(&tmp->time) + 4);
		ft_printf("%s", tmp->file_name);
		if (S_ISLNK(tmp->mode))
			ft_printf(" -> %s", tmp->soft_link);
		ft_putchar('\n');
		tmp = tmp->next;
	}
}

void	print_list_info(t_file *tmp, int max_name)
{
	ft_printf("%s", tmp->file_name);
	ft_putspace((max_name) -
		(long long int)ft_strlen(tmp->file_name));
	ft_putchar('\t');
}

void	print_list(t_dir *dir)
{
	int		rows;
	int		i;
	int		j;
	t_file	*tmp;

	tmp = dir->files;
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
				print_list_info(tmp, dir->max_name);
			j++;
			tmp = tmp->next;
		}
		ft_putchar('\n');
		i++;
	}
}

void	print_one(t_dir *dir)
{
	t_file *tmp;

	tmp = dir->files;
	while (tmp != NULL)
	{
		ft_printf("%s\n", tmp->file_name);
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
		print_list_l(dir);
	else if (opt->one == 1)
		print_one(dir);
	else
		print_list(dir);
}
