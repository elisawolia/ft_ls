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

int			read_dir(char *dirname, t_opt **opt, t_dir *d, int del_r)
{
	t_dir	*direct;
	DIR		*dir;

	dir = opendir(dirname);
	if (!dir)
	{
		ft_printf_fd(1, "\n%s:\n", dirname);
		ft_printf_fd(2, "ft_ls: %s: Permission denied\n", dirname);
		return (-1);
	}
	direct = init_dir(dir, *opt, dirname, d);
	closedir(dir);
	printing(direct, opt);
	if ((*opt)->rec != 1)
		free_dir(&direct);
	if ((*opt)->rec == 1 && del_r == 1)
		free_dir(&direct);
	return (0);
}

static void	add_files(char *file_name, t_dir **dir_files, t_opt **opt)
{
	if (file_name[ft_strlen(file_name) - 1] == '/')
		treat_as_dir(file_name);
	else
		treat_as_file(file_name, dir_files, opt);
}

static void	read_mult_dirs(char **dirname, int i, int argc, t_opt **opt)
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
		{
			dir_next(&direct, init_dir(dir, *opt, dirname[j], NULL));
			if (dir)
				closedir(dir);
		}
		j++;
	}
	sort_mult_dirs(&direct, opt);
	dir_next(&direct, dir_files);
	printing_mult_dir(direct, i, argc, opt);
	if (direct)
		free_dir(&direct);
}

/*
** Main function of ft_ls which shows files and
** folders in a specific or specified directory
*/

int			main(int argc, char **argv)
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
		read_dir(dirname, &opt, NULL, 1);
	else
		read_mult_dirs(argv, i, argc, &opt);
	free(opt);
	free(dirname);
	return (0);
}
