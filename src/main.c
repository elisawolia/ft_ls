/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 13:58:41 by rlintill          #+#    #+#             */
/*   Updated: 2020/03/13 16:29:37 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	read_dir(char *dirname, t_opt **opt, t_dir *d)
{
	t_dir	*direct;
	DIR		*dir;

	dir = opendir(dirname);
	if (!dir)
	{
		perror("diropen");
		exit(1);
	}
	direct = init_dir(dir, *opt, dirname, d);
	closedir(dir);
	printing(direct, opt);
	if ((*opt)->rec != 1 || (!direct->next && !direct->sub && !direct->mult))
		free_dir(&direct);
}

static void	add_files(char *file_name, t_dir **dir_files, t_opt **opt)
{
	struct dirent	*d;
	struct stat		sb;
	DIR				*dir;
	int				added;

	d = NULL;
	added = 0;
	dir = opendir(".");
	if (lstat(".", &sb) == -1)
	{
		ft_printf_fd(2, "ls: %s: No such file or directory\n", file_name);
		return ;
	}
	if (*dir_files == NULL)
		*dir_files = new_dir(".", sb.st_mtime, (long long)sb.st_size);
	(*dir_files)->file_added = 1;
	while ((d = readdir(dir)) != NULL)
	{
		if (ft_strcmp(file_name, d->d_name) == 0)
		{
			file_add(&((*dir_files)->files), new_file(d, *dir_files, NULL));
			added = 1;
		}
	}
	if (added == 0)
		ls_error(file_name);
	sort_files(*opt, *dir_files);
}

void	read_mult_dirs(char **dirname, int i, int argc, t_opt **opt)
{
	t_dir	*direct;
	t_dir	*dir_files;
	DIR		*dir;
	int		j;

	j = i;
	direct = NULL;
	dir_files = NULL;
	while (j < argc)
	{
		if (!(dir = opendir(dirname[j])))
			add_files(dirname[j], &dir_files, opt);
		else
			dir_next(&direct, init_dir(dir, *opt, dirname[j], NULL));
		j++;
	}
	merge_sort_dir(&direct, &def_sort_dir, 0);
	if ((*opt)->s)
		merge_sort_dir(&direct, &size_sort_dir, 0);
	else if ((*opt)->t)
		merge_sort_dir(&direct, &time_sort_dir, 0);
	if ((*opt)->r)
		reverse_dir_mult(&direct);
	dir_next(&direct, dir_files);
	printing_mult_dir(direct, i, argc, opt);
}

/*
** Добавить в конце
** int t = 0;
** while (1)
** t++;
*/

int		main(int argc, char **argv)
{
	t_opt	*opt;
	char	*dirname;
	int		i;

	i = 1;
	opt = malloc_opt();
	dirname = ft_strdup(".");
	while (i < argc)
	{
		if (argv[i][0] == '-')
			read_opt(argv[i], &opt);
		else
			break ;
		i++;
	}
	if (i == argc)
		read_dir(dirname, &opt, NULL);
	else
		read_mult_dirs(argv, i, argc, &opt);
	free(opt);
	free(dirname);
	return (0);
}
