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

void		file_add(t_file **alst, t_file *new)
{
	if (new == NULL)
		return ;
	new->next = (*alst);
	(*alst) = new;
}

void		file_add_full(t_file **alst, t_file *new)
{
	t_file *new_start;

	if (new == NULL)
		return ;
	new_start = new;
	while (new->next != NULL)
		new = new->next;
	new->next = (*alst);
	(*alst) = new_start;
}

static void	soft_link(struct stat sb, t_file *file, char *f_name)
{
	ssize_t		nbytes;
	ssize_t		bufsiz;

	nbytes = 0;
	bufsiz = sb.st_size + 1;
	if (sb.st_size == 0)
		bufsiz = 1024;
	if (S_ISLNK(file->mode))
	{
		if (!(file->soft_link = ft_memalloc(sb.st_size)))
			malloc_err();
		if ((nbytes = readlink(f_name, file->soft_link, bufsiz)) == -1)
		{
			perror("readlink");
			exit(EXIT_FAILURE);
		}
		file->soft_link[nbytes] = '\0';
	}
}

static void	file_info(struct stat sb, t_file *file, int added_d)
{
	file->mode = (unsigned long)sb.st_mode;
	file->uid = (long)sb.st_uid;
	file->gid = (long)sb.st_gid;
	file->link = (long)sb.st_nlink;
	file->size = (long long)sb.st_size;
	file->time = sb.st_mtime;
	file->sec = (long)sb.st_mtimespec.tv_sec;
	file->nsec = (long)sb.st_mtimespec.tv_nsec;
	file->soft_link = NULL;
	file->next = NULL;
	file->added_d = added_d;
}

static char	*get_file_name(char **dir_name, t_dir *dir, struct dirent *d)
{
	char *f_name;

	f_name = NULL;
	if (!(*dir_name = ft_strjoin(dir->name, "/")))
		malloc_err();
	if (!(f_name = ft_strjoin(*dir_name, d->d_name)))
		malloc_err();
	return (f_name);
}

void		free_file_name(char *name, t_file *file)
{
	if (name != NULL && file->file_name != NULL)
		free(file->file_name);
}

t_file		*new_file(struct dirent *d, t_dir *dir, char *name, int added_d)
{
	t_file		*file;
	char		*f_name;
	char		*dir_name;
	char		*new_dir_name;
	struct stat	sb;

	f_name = get_file_name(&dir_name, dir, d);
	if (lstat(f_name, &sb) == -1)
		lstat_error();
	if (!(file = ft_memalloc(sizeof(t_file))))
		malloc_err();
	if (!(file->file_name = ft_strdup(d->d_name)))
		malloc_err();
	if (!(new_dir_name = ft_strjoin(dir_name, file->file_name)))
		malloc_err();
	file_info(sb, file, added_d);
	soft_link(sb, file, f_name);
	dir_info(sb, file, dir, d);
	if (S_ISDIR(file->mode) && ft_findedot(f_name))
		dir_sub(dir, new_dir(new_dir_name, sb.st_mtime, (long long)sb.st_size));
	free_new_file(&f_name, &dir_name, &new_dir_name);
	free_file_name(name, file);
	if (name != NULL && !(file->file_name = ft_strdup(name)))
		malloc_err();
	return (file);
}
