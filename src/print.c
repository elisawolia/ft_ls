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
				tabs(tmp, dir->max_name, j, count_files(dir->files) - rows);
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

void	free_next_file(t_file **files)
{
	t_file *tmp;
	t_file *tmp_next;

	tmp = *files;
	tmp_next = *files;
	while ((tmp_next = tmp_next->next) != NULL)
	{
		tmp->next = NULL;
		tmp = tmp_next;
	}
}

void	free_d(t_dir **dir)
{
	t_file	*files;
	t_file	*fast_file;

	files = (*dir)->files;
	free((*dir)->name);
	free(*dir);
	while (files != NULL && files->added_d == 1)
	{
		fast_file = files->next;
		files->next = NULL;
		files = fast_file;
	}
	while (files != NULL)
	{
		fast_file = files->next;
		if (fast_file != NULL &&
				fast_file->added_d == 1)
			files->next = NULL;
		files = fast_file;
	}
}

void	check_files(t_dir *dir)
{
	t_file	*file;

	file = dir->files;
	while (file != NULL)
	{
		dir->max_link = max(dir->max_link,
							count_max(file->link));
		dir->max_uid = max(dir->max_uid,
							(int)ft_strlen(getpwuid(file->uid)->pw_name));
		dir->max_gid = max(dir->max_gid,
							(int)ft_strlen(getgrgid(file->gid)->gr_name));
		dir->max_name = max(dir->max_name, (int)ft_strlen(file->file_name));
		dir->max_size = max(dir->max_size, count_max(file->size));
		file = file->next;
	}
}

void	print_d(t_opt *opt, t_dir *dir)
{
	t_file	*files;
	t_dir	*tmp;
	t_dir	*temp_dir;

	tmp = dir;
	files = NULL;
	while (tmp != NULL)
	{
		file_add_full(&(files), tmp->files);
		tmp = tmp->mult;
	}
	if (!(temp_dir = new_dir("", 0, 0)))
		return ;
	temp_dir->files = files;
	check_files(temp_dir);
	sort_files(opt, temp_dir);
	if (opt->l == 1)
		print_list_l(temp_dir, opt->g);
	else if (opt->one == 1)
		print_one(temp_dir, opt->g);
	else
		print_list(temp_dir, opt->g);
	free_d(&temp_dir);
}
