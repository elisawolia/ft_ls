/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_mult.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 13:58:41 by rlintill          #+#    #+#             */
/*   Updated: 2020/08/07 16:29:37 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	add_files_help(t_dir **dir_files, struct dirent	*d,
												int *added)
{
	file_add(&((*dir_files)->files), new_file(d, *dir_files, NULL, 0));
	*added = 1;
	(*dir_files)->file_added = 1;
}

void		treat_as_file(char *file_name, t_dir **dir_files, t_opt **opt)
{
	struct dirent	*d;
	struct stat		sb;
	DIR				*dir;
	int				added;

	d = NULL;
	added = 0;
	dir = opendir(".");
	if (lstat(".", &sb) != -1)
	{
		if (*dir_files == NULL)
			*dir_files = new_dir(".", sb.st_mtime, sb.st_size, sb.st_mtimespec);
		while ((d = readdir(dir)) != NULL)
		{
			if (ft_strcmp(file_name, d->d_name) == 0)
				add_files_help(dir_files, d, &added);
		}
		if (added == 0)
			err_help(*opt, file_name);
		sort_files(*opt, *dir_files);
	}
	closedir(dir);
}

static char	*make_dir_name(char *name)
{
	char	*dir_name;

	if (!(dir_name = ft_memalloc(sizeof(char) * ft_strlen(name))))
		malloc_err();
	dir_name = ft_strncpy(dir_name, name, ft_strlen(name) - 1);
	dir_name[ft_strlen(name) - 1] = '\0';
	return (dir_name);
}

static void	treat_as_dir_help(struct dirent	*d, char *dir_name, int *found)
{
	if (ft_strcmp(dir_name, d->d_name) == 0)
	{
		*found = 1;
		if (d->d_type != DT_DIR)
			ft_printf_fd(2, "ft_ls: %s/: Not a directory\n", dir_name);
		else
			ft_printf_fd(2, "ft_ls: %s: Permission denied\n", dir_name);
	}
}

void		treat_as_dir(char *name)
{
	char			*dir_name;
	struct dirent	*d;
	struct stat		sb;
	DIR				*dir;
	int				found;

	d = NULL;
	found = 0;
	dir = opendir(".");
	dir_name = make_dir_name(name);
	if (lstat(".", &sb) != -1)
	{
		while ((d = readdir(dir)) != NULL)
			treat_as_dir_help(d, dir_name, &found);
	}
	if (found == 0)
		ls_error(name);
	closedir(dir);
	if (dir_name)
		free(dir_name);
}
