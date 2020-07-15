/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 13:58:41 by rlintill          #+#    #+#             */
/*   Updated: 2020/03/13 16:29:37 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir	*new_dir(char *name, time_t time, long long size)
{
	t_dir	*dir;

	dir = NULL;
	if (!(dir = ft_memalloc(sizeof(t_dir))))
		malloc_err();
	if (!(dir->name = ft_strdup(name)))
		malloc_err();
	dir->file_added = 0;
	dir->max_link = 0;
	dir->max_uid = 0;
	dir->max_gid = 0;
	dir->max_size = 0;
	dir->max_name = 0;
	dir->total = 0;
	dir->size = size;
	dir->files = NULL;
	dir->time = time;
	dir->sub = NULL;
	dir->next = NULL;
	dir->mult = NULL;
	return (dir);
}

void	dir_sub(t_dir *dir, t_dir *new)
{
	t_dir	*tmp;

	tmp = dir;
	if (new == NULL)
		return ;
	if (!tmp->sub)
		dir->sub = new;
	else
	{
		tmp = tmp->sub;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	dir_next(t_dir **alst, t_dir *new)
{
	if (new == NULL)
		return ;
	new->mult = (*alst);
	(*alst) = new;
}

void	sort_files(t_opt *opt, t_dir *direct)
{
	merge_sort(&(direct->files), &def_sort);
	if (opt->t)
	{
		merge_sort(&(direct->files), &time_sort_nsec);
		merge_sort(&(direct->files), &time_sort_sec);
		merge_sort(&(direct->files), &time_sort);
	}
	if (opt->s)
		merge_sort(&(direct->files), &size_sort);
	if (opt->r)
		reverse(&(direct->files));
}

t_dir	*init_dir(DIR *dir, t_opt *opt, char *name, t_dir *di)
{
	struct dirent	*d;
	t_dir			*direct;
	struct stat		sb;

	d = NULL;
	if (lstat(name, &sb) == -1)
		lstat_error();
	direct = (di != NULL) ? di
	: new_dir(name, sb.st_mtime, (long long)sb.st_size);
	while ((d = readdir(dir)) != NULL)
	{
		if (opt->d)
		{
			if (!ft_strcmp(d->d_name, "."))
			{
				file_add(&(direct->files), new_file(d, direct, name));
				break ;
			}
			continue;
		}
		if ((d->d_name[0] != '.' && !opt->a) || opt->a)
			file_add(&(direct->files), new_file(d, direct, NULL));
	}
	sort_files(opt, direct);
	return (direct);
}
