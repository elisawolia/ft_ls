/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 13:58:41 by rlintill          #+#    #+#             */
/*   Updated: 2020/08/05 16:29:37 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	free_d(t_dir **dir)
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

static void	check_files(t_dir *dir)
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

void		print_d(t_opt *opt, t_dir *dir)
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
