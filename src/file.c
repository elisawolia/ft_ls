/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 13:58:41 by rlintill          #+#    #+#             */
/*   Updated: 2020/03/13 16:29:37 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	file_add(t_file **alst, t_file *new)
{
	if (new == NULL)
		return ;
	new->next = (*alst);
	(*alst) = new;
}

void	free_files(t_file **list)
{
	if ((*list)->file_name)
		free((*list)->file_name);
	if ((*list)->next)
		free_files(&((*list)->next));
	free(*list);
}

t_file	*new_file(struct dirent *d, t_dir *dir)
{
	t_file		*file;
	char		*f_name;
	char		*dir_name;
	char		*new_dir_name;
	struct stat	sb;

	if (!(dir_name = ft_strjoin(dir->name, "/")))
	{
		perror("malloc");
		exit(1);
	}
	if (!(f_name = ft_strjoin(dir_name, d->d_name)))
	{
		free(dir_name);
		perror("malloc");
		exit(1);
	}
	if (lstat(f_name, &sb) == -1)
	{
		perror("lstat");
		exit(EXIT_FAILURE);
	}
	if (!(file = ft_memalloc(sizeof(t_file))))
	{
		perror("malloc");
		exit(1);
	}
	if (!(file->file_name = ft_strdup(d->d_name)))
	{
		perror("malloc");
		exit(1);
	}
	if (!(new_dir_name = ft_strjoin(dir_name, file->file_name)))
	{
		free(dir_name);
		free(f_name);
		perror("malloc");
		exit(1);
	}
	dir->total += (long long)sb.st_blocks;
	file->mode = (unsigned long)sb.st_mode;
	if (S_ISDIR(file->mode) && ft_findedot(f_name))
	{
		dir_sub(dir, new_dir(new_dir_name, sb.st_mtime, (long long)sb.st_size));
	}
	file->uid = (long)sb.st_uid;
	file->gid = (long)sb.st_gid;
	file->link = (long)sb.st_nlink;
	file->size = (long long)sb.st_size;
	file->time = sb.st_mtime;
	file->next = NULL;
	dir->max_uid = MAX(dir->max_uid,
							(int)ft_strlen(getpwuid(file->uid)->pw_name));
	dir->max_gid = MAX(dir->max_gid,
							(int)ft_strlen(getgrgid(file->gid)->gr_name));
	dir->max_name = MAX(dir->max_name, (int)ft_strlen(d->d_name));
	dir->max_size = MAX(dir->max_size, count_max(file->size));
	free(f_name);
	free(dir_name);
	free(new_dir_name);
	return (file);
}