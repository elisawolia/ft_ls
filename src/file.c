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

t_file	*new_file(struct dirent *d, t_dir *dir, char *name)
{
	t_file		*file;
	char		*f_name;
	char		*dir_name;
	char		*new_dir_name;
	struct stat	sb;
	ssize_t		nbytes;
	ssize_t		bufsiz;

	nbytes = 0;
	if (!(dir_name = ft_strjoin(dir->name, "/")))
		malloc_err();
	if (!(f_name = ft_strjoin(dir_name, d->d_name)))
		malloc_err();
	if (lstat(f_name, &sb) == -1)
		lstat_error();
	if (!(file = ft_memalloc(sizeof(t_file))))
		malloc_err();
	if (!(file->file_name = ft_strdup(d->d_name)))
		malloc_err();
	if (!(new_dir_name = ft_strjoin(dir_name, file->file_name)))
		malloc_err();
	bufsiz = sb.st_size + 1;
	if (sb.st_size == 0)
		bufsiz = 1024;
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
	file->sec = (long)sb.st_mtimespec.tv_sec;
	file->nsec = (long)sb.st_mtimespec.tv_nsec;
	file->soft_link = NULL;
	if (S_ISLNK(file->mode))
	{
		if (!(file->soft_link = ft_memalloc(sb.st_size)))
			malloc_err();
		if ((nbytes = readlink(f_name, file->soft_link, bufsiz)) == -1)
		{
			perror("readlink");
			exit(EXIT_FAILURE);
		}
	}
	file->next = NULL;
	dir->max_link = max(dir->max_link,
							count_max(file->link));
	dir->max_uid = max(dir->max_uid,
							(int)ft_strlen(getpwuid(file->uid)->pw_name));
	dir->max_gid = max(dir->max_gid,
							(int)ft_strlen(getgrgid(file->gid)->gr_name));
	dir->max_name = max(dir->max_name, (int)ft_strlen(d->d_name));
	dir->max_size = max(dir->max_size, count_max(file->size));
	free(f_name);
	free(dir_name);
	free(new_dir_name);
	if (name != NULL)
	{
		if (!(file->file_name = ft_strdup(name)))
			malloc_err();
	}
	return (file);
}
